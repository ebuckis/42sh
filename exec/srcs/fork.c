/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 10:59:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 10:13:05 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_fork_pipe : cree le pipeline et fork
** dans le fils, duplique la sortie standard sur le cote ecriture du pipe
** dans le pere, duplique l'entree standard  sur le cote lecture  du pipe
** retourne le pid fils
** on fait appel a cette fonction autant de fois qu'il y a de pipe
*/

static int		ft_fork_pipe(t_parse *p, int *tab_pipe, char ***p_env, int i)
{
	int		pid;
	int		pipeline[2];

	pipe(pipeline);
	pid = fork();
	if (pid < 0)
	{
		close(pipeline[0]);
		close(pipeline[1]);
		ft_putendl_fd("error", 2);
	}
	else if (pid == 0)
	{
		dup2(pipeline[1], STDOUT_FILENO);
		close(pipeline[0]);
		ft_execve(p, tab_pipe[i], p_env);
	}
	else if (pid > 0)
	{
		dup2(pipeline[0], STDIN_FILENO);
		close(pipeline[1]);
		return (pid);
	}
	return (0);
}

/*
** ft_fork_shell3 : verifie que tous les pids des processus pipe soit finit
** dans l'ordre inverse de creation avant de rendre la main pour le wait final.
** si un processus infini (yes. top, base64 ...) se retrouve devant un process
** deja fini, alors on le kill car il ne peut plus avoir d'impact sur lui
** malgre le pipe
*/

static void		ft_fork_shell3(t_parse *p, int *tab_pipe, int *pid_tab,
		int pid)
{
	int			i;
	int			status;

	waitpid(pid, &status, WUNTRACED);
	i = -1;
	while (pid_tab[++i])
		;
	while (--i >= 0)
	{
		if ((ft_strequ(p->arg[tab_pipe[i]], "yes")) ||
				(ft_strequ(p->arg[tab_pipe[i]], "top")) ||
				(ft_strequ(p->arg[tab_pipe[i]], "base64")))
			kill(pid_tab[i], 9);
		waitpid(pid_tab[i], NULL, WUNTRACED);
	}
	exit(ft_ret_display(p, pid, status));
}

/*
** ft_fork_shell2 : lance les forks de pipe et enregistre
** les pids correspondants
*/

static void		ft_fork_shell2(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pip)
{
	int			i;
	int			*pid_tab;
	pid_t		pid;

	i = -1;
	if ((pid_tab = (int*)malloc(sizeof(int) * (nb_pip + 1))))
	{
		pid_tab[nb_pip] = 0;
		i = nb_pip + 1;
		while (--i > 0)
			pid_tab[nb_pip - i] = ft_fork_pipe(p, tab_pipe, p_env, nb_pip - i);
		if (nb_pip)
		{
			pid = fork();
			if (pid == 0)
				ft_execve(p, tab_pipe[nb_pip], p_env);
			else if (pid > 0)
				ft_fork_shell3(p, tab_pipe, pid_tab, pid);
		}
		else
			ft_execve(p, tab_pipe[nb_pip], p_env);
		ft_memdel((void**)&pid_tab);
	}
	else
		exit(1);
}

/*
** ft_fork_shell : gestion des forks et wait
** si zero pipe et builtin cd, unsetenv ou setenv, pas de fork pour modifier
** env
** sinon au moins un fork pour lancer un processus hors du shell
** et un fork supplementaire par pipe present
** on wait le dernier processus lance
*/

void			ft_fork_shell(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe)
{
	pid_t			pid;
	int				status;
	char			**tab_com;

	if (!nb_pipe && (ft_strequ(p->arg[tab_pipe[0]], "cd") ||
		ft_strequ(p->arg[tab_pipe[0]], "setenv") ||
		ft_strequ(p->arg[tab_pipe[0]], "unsetenv")))
	{
		tab_com = manage_redir(p, tab_pipe[0], p_env, 1);
		run_builtin(p, tab_com, p_env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			ft_fork_shell2(p, tab_pipe, p_env, nb_pipe);
		else if (pid > 0)
		{
			waitpid(pid, &status, WUNTRACED);
			ft_ret_display(p, pid, status);
		}
	}
}
