/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redir.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 13:32:47 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 15:54:52 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

static int		ft_relative_absolute(char *doc)
{
	if (doc[0] == '/')
		return (1);
	else
		return (0);
}

/*
** recuperer le path complet d'un fichier
*/

char			*get_path_redir(t_parse *p, int *i, char **env)
{
	char	*pwd;
	char	*tmp;
	char	*path;
	int		nb;

	(*i)++;
	nb = ft_relative_absolute(p->arg[*i]);
	if (nb == -1)
		return (NULL);
	else if (nb == 1)
		return (ft_strdup(p->arg[*i]));
	pwd = ft_getpwd(env, 0);
	tmp = ft_strjoin(pwd, "/");
	path = ft_strjoin(tmp, p->arg[*i]);
	ft_strdel(&pwd);
	ft_strdel(&tmp);
	return (path);
}

/*
** gestion des closes
*/

static int		ft_redir_close(t_parse *p, int *i)
{
	int		fd;

	if (!ft_strcmp(p->arg[*i], ">&-") || !ft_strcmp(p->arg[*i], "1>&-"))
	{
		fd = 1;
		close(fd);
	}
	else if ((fd = ft_atoi(p->arg[*i])) >= 0 && ft_strstr(p->arg[*i], ">&-"))
		close(fd);
	else
		ft_putendl_fd("redirection parse error", 2);
	return (fd);
}

/*
** gestion des heredoc
*/

static int		ft_redir_heredoc(t_parse *p, int *i, char **env)
{
	char		*home;
	char		*tmp;
	char		*path;
	int			fd;

	(*i)++;
	home = ft_home(env);
	tmp = ft_strjoin(home, "/");
	path = ft_strjoin(tmp, ".heredoc");
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
	{
		ft_putstr_fd(p->arg[*i], fd);
		close(fd);
		fd = open(path, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	ft_strdel(&home);
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (fd);
}

/*
** gestion des redirs in, out, close, heredoc
*/

void			ft_redir(t_parse *p, int *redir_lim, char **env,
		int nb_redirec)
{
	int		i;
	int		fd;

	fd = 0;
	if (nb_redirec)
	{
		i = redir_lim[1] - 1;
		while (p->arg[++i] && p->arg_id[i][0] < PIPE)
		{
			if (ft_strchr(p->arg[i], '-'))
				fd = ft_redir_close(p, &i);
			else if (ft_strchr(p->arg_id[i], HEREDOC))
				fd = ft_redir_heredoc(p, &i, env);
			else
			{
				if (ft_strchr(p->arg[i], '>'))
					fd = ft_redir_out(p, &i, env);
				else if (ft_strchr(p->arg[i], '<'))
					fd = ft_redir_in(p, &i, env);
			}
		}
	}
	if (fd < 0)
		exit(1);
}
