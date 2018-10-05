/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execve.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 11:01:31 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 10:12:50 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_execve warning : check si on les droits d'exec sur le binaire et que
** c'est bien un regular file
*/

static void		ft_execve_warning(char *path, char **tab_com)
{
	if (access(path, X_OK))
		ft_putstr_fd("21sh: permission denied: ", 2);
	else
		ft_putstr_fd("21sh: not a regular file: ", 2);
	ft_putstr_fd(tab_com[0], 2);
	ft_putstr_fd("\n", 2);
	ft_free_tab(&tab_com);
	exit(126);
}

/*
** ft_execve : check si il y a des redir puis si c'est un buitlin ou un
** binaire sinon retourne le code 127, command not found;
*/

void			ft_execve(t_parse *p, int tab_pipe_i, char ***p_env)
{
	char			*path;
	char			**tab_com;
	struct stat		buf;
	int				ret;

	if (!p->arg[tab_pipe_i][0])
		exit(0);
	tab_com = manage_redir(p, tab_pipe_i, p_env, 0);
	if (check_builtin(tab_com))
		run_builtin_fork(p, tab_com, p_env, tab_pipe_i);
	else
	{
		path = check_bin(tab_com, *p_env);
		if (path && !access(path, X_OK) && ((ret = stat(path, &buf)) == 0) &&
				(buf.st_mode & S_IFREG))
			execve(path, tab_com, *p_env);
		else if (path)
			ft_execve_warning(path, tab_com);
		else
		{
			ft_free_tab(&tab_com);
			exit(127);
		}
	}
	ft_free_tab(&tab_com);
}
