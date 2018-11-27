/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execve.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 11:01:31 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 14:57:26 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_execve warning : check si on les droits d'exec sur le binaire et que
** c'est bien un regular file
*/

static int		ft_execve_warning(char *path, char **tab_com)
{
	if (access(path, X_OK))
		ft_putstr_fd("42sh: permission denied: ", 2);
	else
		ft_putstr_fd("42sh: not a regular file: ", 2);
	ft_putstr_fd(tab_com[0], 2);
	ft_putstr_fd("\n", 2);
	return (126);
}

/*
** ft_check_execve : check si l'executable ou le builtin existe
*/

static int		ft_check_exec(t_parse *p, int tab_pipe_i, char ***p_env)
{
	char			*path;
	char			**tab_com;
	struct stat		buf;
	int				ret;

	if (!p->arg[tab_pipe_i][0])
		return (0);
	tab_com = manage_redir(p, tab_pipe_i, p_env, 0);
	if (check_builtin(tab_com))
		ret = 0;
	else
	{
		if ((path = check_bin(tab_com, *p_env)) && !access(path, X_OK) &&
				((ret = stat(path, &buf)) == 0) && (buf.st_mode & S_IFREG))
			ret = 0;
		else if (path)
			ret = ft_execve_warning(path, tab_com);
		else
			ret = 127;
		ft_memdel((void**)&path);
	}
	ft_free_tab(&tab_com);
	return (ret);
}

/*
** ft_check_all_execve : check si l'executable ou le builtin existe pour chaque
** pipe
*/

int				ft_check_all_exec(t_parse *p, int *tab_pipe, char ***p_env)
{
	int		i;
	int		ret;

	i = -1;
	while (tab_pipe[++i] >= 0)
	{
		ret = ft_check_exec(p, tab_pipe[i], p_env);
		p->ret = (ret > p->ret || i == 0) ? ret : p->ret;
	}
	return (p->ret);
}

/*
** ft_execve : check si il y a des redir puis lance le buitlin ou le binaire
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
		run_builtin_exit(p, tab_com, p_env, tab_pipe_i);
	else
	{
		path = check_bin(tab_com, *p_env);
		if (path && !access(path, X_OK) && ((ret = stat(path, &buf)) == 0) &&
				(buf.st_mode & S_IFREG))
			execve(path, tab_com, *p_env);
	}
	ft_free_tab(&tab_com);
}
