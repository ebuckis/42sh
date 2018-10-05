/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_redir_out.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 11:53:11 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 15:54:03 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_simple_double_out: gere les redirections de sortie "> file" et ">> file"
*/

static int		ft_simple_double_out(t_parse *p, int *i, char **env, int nb)
{
	char	*path;
	int		fd;

	path = get_path_redir(p, i, env);
	fd = 0;
	if (nb == 1)
	{
		if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
			dup2(fd, STDOUT_FILENO);
	}
	else
	{
		if ((fd = open(path, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
			dup2(fd, STDOUT_FILENO);
	}
	ft_strdel(&path);
	return (fd);
}

/*
** ft_fd_redir_and : gere la redirection de sortie "&> file"
*/

static int		ft_redir_and(t_parse *p, int *i, char **env)
{
	char	*path;
	int		fd;

	path = get_path_redir(p, i, env);
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
	}
	ft_strdel(&path);
	return (fd);
}

/*
** ft_fd_redir : gere la redirection de sortiei "n> file"
*/

static int		ft_fd_redir(t_parse *p, int *i, char **env, int n)
{
	char	*path;
	int		fd;
	char	*pt;

	if ((pt = ft_strstr(p->arg[*i], ">>")) && !pt[2])
	{
		path = get_path_redir(p, i, env);
		if ((fd = open(path, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
			dup2(fd, n);
	}
	else
	{
		path = get_path_redir(p, i, env);
		if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
			dup2(fd, n);
	}
	ft_strdel(&path);
	return (fd);
}

/*
** ft_redir_outi2 : gere les differentes redirections de sortie >, >>, >&
** gestion de la redirection "n>&m"
*/

static int		ft_redir_out2(t_parse *p, int *i, char **env)
{
	int		fd;
	int		m;
	int		n;
	char	*pt;

	fd = 0;
	if (!ft_strcmp(p->arg[*i], ">"))
		fd = ft_simple_double_out(p, i, env, 1);
	else if (!ft_strcmp(p->arg[*i], ">>"))
		fd = ft_simple_double_out(p, i, env, 2);
	else if (!ft_strcmp(p->arg[*i], ">&"))
		fd = ft_redir_and(p, i, env);
	else if ((n = ft_atoi(p->arg[*i])) >= 0
		&& (pt = ft_strchr(p->arg[*i], '>')) && !pt[1])
		fd = ft_fd_redir(p, i, env, n);
	else if ((pt = ft_strstr(&(p->arg[*i][1]), ">&")) && pt[2])
	{
		n = ft_atoi(p->arg[*i]);
		m = ft_atoi(&(pt[2]));
		dup2(m, n);
	}
	else
		return (-2);
	return (fd);
}

/*
** ft_redir_out : gere les differentes redirections de sortie >
** gestion de la redirection ">&m"
** gestion des cas/pattern d'erreurs
** ou permission denied si fd = - 1 impossible open file
*/

int				ft_redir_out(t_parse *p, int *i, char **env)
{
	int		m;
	int		fd;
	char	*pt;

	if ((fd = ft_redir_out2(p, i, env)) != -2)
		;
	else if ((m = ft_atoi(p->arg[*i])) >= 0
		&& (pt = ft_strstr(p->arg[*i], ">>")) && !pt[2])
		fd = ft_fd_redir(p, i, env, m);
	else if ((pt = ft_strstr(p->arg[*i], ">&")) && pt[2]
		&& (m = ft_atoi(&(pt[2]))) >= 0)
	{
		dup2(m, STDOUT_FILENO);
		dup2(m, STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd("redirection parse error", 2);
		return (-1);
	}
	if (fd < 0)
		ft_putendl_fd_arg("21sh: Permission denied: ", p->arg[*i]);
	return (fd);
}
