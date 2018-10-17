/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 10:59:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 12:08:46 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

static int		**ft_make_tab_pipe_fd(int nb_pipe)
{
	int		**tab_pipe_fd;
	int		i;
	int		pipeline[2];

	tab_pipe_fd = (int**)malloc(sizeof(int*) * (nb_pipe + 2));
	tab_pipe_fd[nb_pipe + 1] = NULL;
	i = -1;
	while (++i <= nb_pipe)
	{
		tab_pipe_fd[i] = (int*)malloc(sizeof(int) * 2);
		if (i > 0)
		{
			pipe(pipeline);
			tab_pipe_fd[i - 1][1] = pipeline[1];
			tab_pipe_fd[i][0] = pipeline[0];
		}
	}
	tab_pipe_fd[0][0] = 0;
	tab_pipe_fd[nb_pipe][1] = 1;
	return (tab_pipe_fd);
}

/*
** ft_fork_pipe : cree le pipeline et fork
** dans le fils, duplique la sortie standard sur le cote ecriture du pipe
** dans le pere, duplique l'entree standard  sur le cote lecture  du pipe
** retourne le pid fils
** on fait appel a cette fonction autant de fois qu'il y a de pipe
*/

static int		ft_fork_pipe(t_parse *p, int tab_pipe_i, char ***p_env,
		int **tab_pipe_fd, int i)
{
	int		pid;
	int		j;

	pid = fork();
	if (pid == 0)
	{
		dup2(tab_pipe_fd[i][0], STDIN_FILENO);
		dup2(tab_pipe_fd[i][1], STDOUT_FILENO);
		j = -1;
		while (tab_pipe_fd[++j])
		{
			if (j != i && tab_pipe_fd[j][0] != 0)
				close(tab_pipe_fd[j][0]);
			if (j != i && tab_pipe_fd[j][1] != 1)
				close(tab_pipe_fd[j][1]);
		}
		ft_execve(p, tab_pipe_i, p_env);
	}
	else if (pid > 0)
	{
		if (tab_pipe_fd[i][0] != 0)
			close(tab_pipe_fd[i][0]);
		if (tab_pipe_fd[i][1] != 1)
			close(tab_pipe_fd[i][1]);
		return (pid);
	}
	return (0);
}

/*
** ft_fork_shell2 : lance les forks de pipe et enregistre
** les pids correspondants puis attend la fin de tous les processus
** avant d'exit avec le code retour du dernier processus
*/

static int		ft_fork_shell2(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe)
{
	int			*tab_pid;
	int			last_pid;
	int			**tab_pipe_fd;
	int			status;
	int			i;

	tab_pid = (int*)malloc(sizeof(int) * (nb_pipe + 2));
	tab_pid[nb_pipe + 1] = 0;
	tab_pipe_fd = ft_make_tab_pipe_fd(nb_pipe);
	i = nb_pipe + 1;
	while (--i >= 0)
		tab_pid[i] = ft_fork_pipe(p, tab_pipe[i], p_env, tab_pipe_fd, i);
	i = -1;
	while (tab_pid[++i])
		waitpid(tab_pid[i], &status, WUNTRACED);
	last_pid = tab_pid[--i];
	ft_memdel((void**)&tab_pid);
	//free tab_pipe_fd
	ft_ret_display(p, last_pid, status, p->arg[tab_pipe[0]]);
	return (last_pid);
	exit(ft_ret_display(p, last_pid, status, p->arg[tab_pipe[0]]));
}

/*
** ft_fork_shell : gestion des forks et wait
** si zero pipe et builtin cd, unsetenv ou setenv, pas de fork pour modifier
** env sinon ft_fork_shell2
*/

void			ft_fork_shell(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe)
{
	char			**tab_com;

	if (!nb_pipe && (ft_strequ(p->arg[tab_pipe[0]], "cd") ||
		ft_strequ(p->arg[tab_pipe[0]], "setenv") ||
		ft_strequ(p->arg[tab_pipe[0]], "unsetenv")))
	{
		tab_com = manage_redir(p, tab_pipe[0], p_env, 1);
		run_builtin(p, tab_com, p_env);
	}
	else
		ft_fork_shell2(p, tab_pipe, p_env, nb_pipe);
}
