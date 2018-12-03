/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 10:59:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 09:48:48 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** tableau de tous les fd de pipe ouvert pour duper ensuite les stdin et stout
** de chaque process
*/

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

static void		ft_memdel_tab_pipe_fd(int **tab_pipe_fd)
{
	int		i;

	i = -1;
	while (tab_pipe_fd[++i])
		ft_memdel((void**)&tab_pipe_fd[i]);
	ft_memdel((void**)&tab_pipe_fd);
}

/*
** ft_fork_pipe : creer le fork pour chaque commande
** dans le fils, dup l'entree  standard sur le cote lecture du pipe precedant
** et dup la sortie standard sur le cote ecriture du pipe suivant
** et ferme les fd ouverts inutiles
** dans le pere,
** et on retourne le pid fils pour le memoriser ensuite dans tab_pid
** on fait appel a cette fonction autant de fois qu'il y a de pipe + 1
*/

static int		ft_fork_pipe(t_parse *p, int tab_pipe_i, char ***p_env,
		int **tab_fd)
{
	int		pid;
	int		j;

	pid = fork();
	if (pid == 0)
	{
		dup2(tab_fd[p->k][0], STDIN_FILENO);
		dup2(tab_fd[p->k][1], STDOUT_FILENO);
		j = -1;
		while (tab_fd[++j])
		{
			pid = (j != p->k && tab_fd[j][0] != 0) ? close(tab_fd[j][0]) : 0;
			pid = (j != p->k && tab_fd[j][1] != 1) ? close(tab_fd[j][1]) : 0;
		}
		ft_execve(p, tab_pipe_i, p_env);
	}
	else if (pid > 0)
	{
		j = (tab_fd[p->k][0] != 0) ? close(tab_fd[p->k][0]) : 0;
		j = (tab_fd[p->k][1] != 1) ? close(tab_fd[p->k][1]) : 0;
		return (pid);
	}
	return (0);
}

/*
** ft_fork_shell2 : lance les forks de pipe et enregistre
** les pids correspondants puis attend la fin de tous les processus
** avant d'exit avec le code retour du dernier processus
*/

static void		ft_fork_shell2(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe)
{
	int			*tab_pid;
	int			**tab_pipe_fd;
	int			status;
	int			i;

	tab_pid = (int*)malloc(sizeof(int) * (nb_pipe + 2));
	tab_pid[nb_pipe + 1] = 0;
	tab_pipe_fd = ft_make_tab_pipe_fd(nb_pipe);
	i = -1;
	while (++i <= nb_pipe)
	{
		p->k = i;
		tab_pid[i] = ft_fork_pipe(p, tab_pipe[i], p_env, tab_pipe_fd);
	}
	i = -1;
	while (tab_pid[++i])
	{
		waitpid(tab_pid[i], &status, WUNTRACED);
		if (WIFSTOPPED(status) && WSTOPSIG(status) == 18)
			kill(tab_pid[i], 9);
	}
	ft_ret_display(p, tab_pid[--i], status);
	ft_memdel((void**)&tab_pid);
	ft_memdel_tab_pipe_fd(tab_pipe_fd);
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
	char			*exec;

	exec = NULL;
	if (ft_check_all_exec(p, tab_pipe, p_env))
		;
	else if (!nb_pipe && check_builtin2(&(p->arg[tab_pipe[0]])))
	{
		tab_com = manage_redir(p, tab_pipe[0], p_env, 1);
		run_builtin_free(p, tab_com, p_env, tab_pipe[0]);
	}
	else
		ft_fork_shell2(p, tab_pipe, p_env, nb_pipe);
	ft_memdel((void**)&exec);
}
