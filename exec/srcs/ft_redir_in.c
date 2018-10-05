/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_redir_in.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 11:55:19 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 15:53:14 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_get_redir_fd1 : gere la redirection "< file"
*/

static int		ft_get_redir_fd1(t_parse *p, int *i, char **env)
{
	char	*path;
	int		fd;

	path = get_path_redir(p, i, env);
	if ((fd = open(path, O_RDONLY)) >= 0)
		dup2(fd, STDIN_FILENO);
	ft_strdel(&path);
	return (fd);
}

/*
** ft_get_redir_fd2 : gere la redirection "n< file"
*/

static int		ft_get_redir_fd2(t_parse *p, int *i, char **env, int n)
{
	int		fd;
	char	*path;

	path = get_path_redir(p, i, env);
	if ((fd = open(path, O_RDONLY)) >= 0)
		dup2(fd, n);
	ft_strdel(&path);
	return (fd);
}

/*
** ft_redir_in : gere les differentes redirections d'entree <
** gestion de la redirection "n<m"
** gestion des cas/pattern d'erreurs
** ou permission denied si fd = - 1 impossible open file
*/

int				ft_redir_in(t_parse *p, int *i, char **env)
{
	int		fd;
	int		n;
	int		m;
	char	*pt;

	fd = 0;
	pt = ft_strchr(p->arg[*i], '<');
	if (!ft_strcmp(p->arg[*i], "<"))
		fd = ft_get_redir_fd1(p, i, env);
	else if ((n = ft_atoi(p->arg[*i])) >= 0 && pt && !pt[1])
		fd = ft_get_redir_fd2(p, i, env, n);
	else if ((n = ft_atoi(p->arg[*i])) >= 0 &&
		(pt = ft_strstr(&(p->arg[*i][1]), "<&")) && pt[2] &&
		(m = ft_atoi(&(pt[2])))
		>= 0)
		dup2(m, n);
	else
	{
		ft_putendl_fd("redirection parse error", 2);
		return (-1);
	}
	if (fd < 0)
		ft_putendl_fd_arg("21sh: Permission denied: ", p->arg[*i]);
	return (fd);
}
