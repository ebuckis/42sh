/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 10:59:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 11:27:04 by bpajot      ###    #+. /#+    ###.fr     */
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
	i = -1;
	//while (++i <= nb_pipe)
	//	ft_printf("tab_pipe_fd[%d][0] = %d [%d][1] = %d\n", i, tab_pipe_fd[i][0],
	//		i, tab_pipe_fd[i][1]);
	return(tab_pipe_fd);
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
		if (tab_pipe_fd[i][0] != 0)
		{
		//	ft_printf("dup2(pipe[0] = %d, STDIN)\n", tab_pipe_fd[i][0]);
			dup2(tab_pipe_fd[i][0], STDIN_FILENO);
		}
		if (tab_pipe_fd[i][1] != 1)
		{
		//	ft_printf("dup2(pipe[1] = %d, STDOUT)\n", tab_pipe_fd[i][1]);
			dup2(tab_pipe_fd[i][1], STDOUT_FILENO);
		}
		j = -1;
		while(tab_pipe_fd[++j])
		{
			if (j != i && tab_pipe_fd[j][0] != 0)
				close(tab_pipe_fd[j][0]);
			if (j != i && tab_pipe_fd[j][1] != 1)
				close(tab_pipe_fd[j][1]);
		}
		//ft_printf("execve: %s\n", p->arg[tab_pipe_i]);
		ft_execve(p, tab_pipe_i, p_env);
	}
	else if (pid > 0)
	{
		if (tab_pipe_fd[i][0] != 0)
			close(tab_pipe_fd[i][0]);
		if (tab_pipe_fd[i][1] != 1)
			close(tab_pipe_fd[i][1]);
		//ft_printf(" %s -> pid = %d\n", p->arg[tab_pipe_i], pid);
		return(pid);
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
		int** tab_pipe_fd)
{
	int			i;
	int			status;

	i = -1;
	while (pid_tab[++i])
	{
		//ft_printf("pid = %d waiting\n", pid_tab[i]);
		waitpid(pid_tab[i], &status, WUNTRACED);
		//ft_printf("pid = %d finish\n", pid_tab[i]);
		if (tab_pipe_fd[i][0] != 0)
		{
		//	ft_printf("close tab_pipe_fd[%d][0] = %d\n", i, tab_pipe_fd[i][0]);
			close(tab_pipe_fd[i][0]);
		}
		if (tab_pipe_fd[i][1] != 1)
		{
		//	ft_printf("close tab_pipe_fd[%d][1] = %d\n", i, tab_pipe_fd[i][1]);
			close(tab_pipe_fd[i][1]);
		}
	}
	exit(ft_ret_display(p, pid_tab[i], status, p->arg[tab_pipe[0]]));
}

/*
** ft_fork_shell2 : lance les forks de pipe et enregistre
** les pids correspondants
*/

static void		ft_fork_shell2(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe)
{
	int			*pid_tab;
	int			**tab_pipe_fd;
	int			i;
	//int			pipeline[2];

	pid_tab = (int*)malloc(sizeof(int) * (nb_pipe + 2));
	pid_tab[nb_pipe + 1] = 0;
	tab_pipe_fd = ft_make_tab_pipe_fd(nb_pipe);
	i = nb_pipe + 1;
	while ( --i >= 0)
	{
		//pipeline[0] = tab_pipe_fd[i][0];
		//pipeline[1] = tab_pipe_fd[i][1];
		pid_tab[i] = ft_fork_pipe(p, tab_pipe[i], p_env, tab_pipe_fd, i);
	}
		//ft_printf("i = %d pid = %d commande = %s\n", i, pid_tab[i], p->arg[tab_pipe[i]]);
		//	}
		//	pid = fork();
		//	if (pid == 0)
		//	{
		//		ft_printf("execve: %s\n", p->arg[tab_pipe[nb_pip]]);
		//		ft_execve(p, tab_pipe[nb_pip], p_env);
		//	}
		//	else if (pid > 0)
		ft_fork_shell3(p, tab_pipe, pid_tab, tab_pipe_fd);
		//}
		//else
		//	ft_execve(p, tab_pipe[nb_pip], p_env);
	ft_memdel((void**)&pid_tab);
	//}
	//else
	//	exit(1);
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
			ft_ret_display(p, pid, status, p->arg[tab_pipe[0]]);
		}
	}
}
