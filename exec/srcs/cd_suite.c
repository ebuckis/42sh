/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_suite.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/06 10:44:28 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 13:14:04 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**  Verif si str est un repertoire valid et accessible
*/

static int		verif_rep(char *str)
{
	struct stat	buf;

	if (str == NULL)
		return (1);
	if (ft_strncmp(str, "-", 1) == 0)
	{
		usage_cd(str);
		return (1);
	}
	if (stat(str, &buf) != 0)
	{
		ft_putendl_fd_arg("cd: no such file or directory: ", str);
		return (1);
	}
	else if (!(buf.st_mode & S_IFDIR) || (buf.st_mode & S_IFCHR))
	{
		ft_putendl_fd_arg("cd: not a directory: ", str);
		return (1);
	}
	else if (access(str, X_OK))
	{
		ft_putendl_fd_arg("cd: permission denied: ", str);
		return (1);
	}
	return (0);
}

/*
**  Verif repertoire spe (- et ~)
*/

static char		*verif_cd_spe(char *str)
{
	char		*target;

	target = NULL;
	if (str == NULL)
		return (NULL);
	if (ft_strcmp(str, "-") == 0)
		target = ft_strdup("oldpwd");
	if (ft_strcmp(str, "~") == 0)
		target = ft_strdup("cd");
	return (target);
}

/*
**  retourne le lien symbolique
*/

static char		*ret_link_symbol(char *rep)
{
	char		*buf;
	char		*target;

	target = NULL;
	buf = NULL;
	if (rep == NULL)
		return (NULL);
	buf = ft_strnew(255);
	if (readlink(rep, buf, 255) == -1)
	{
		ft_strdel(&buf);
		target = ft_strdup(rep);
		return (target);
	}
	if (ft_strlen(buf) == 0)
		target = ft_strdup("/");
	else
		target = ft_strdup(buf);
	ft_strdel(&buf);
	return (target);
}

/*
**  builtins cd avec option -L ou -P
**  return le repertoire ou aller en fonction des options
**  -P -> Force le suivis des liens symboliques
**  -L -> Force enchainement reel des repertoires
*/

static int		check_options_cd(char *arg, int *l, int *p)
{
	if (arg == NULL)
		return (1);
	if (ft_strcmp(arg, "-L") == 0)
	{
		*l = 1;
		*p = 0;
	}
	else if (ft_strcmp(arg, "-P") == 0)
	{
		*p = 1;
		*l = 0;
	}
	return (0);
}

char			*ret_target(char **arg, int l, int p, int q)
{
	char		*target;
	int			i;

	target = NULL;
	i = 1;
	while (arg[i] && q == 0)
	{
		check_options_cd(arg[i], &l, &p);
		if (arg[i] == NULL)
			q = 1;
		else if (ft_strcmp(arg[i], "-L") != 0 && ft_strcmp(arg[i], "-P") != 0)
		{
			if ((target = verif_cd_spe(arg[i])) != NULL)
				return (target);
			if (verif_rep(arg[i]) == 1)
				return (NULL);
			q = i;
		}
		i++;
	}
	if (p == 1)
		return (target = ret_link_symbol(arg[q]));
	return (target = ft_strdup(arg[q]));
}
