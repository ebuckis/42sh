/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_suite.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 10:50:52 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 10:27:43 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
<<<<<<< HEAD
=======
**  Usage cd + print error
*/

void			usage_cd(char *str)
{
	if (str != NULL)
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	ft_putstr_fd("cd: usage: cd [-L|-P] [dir]\n", 2);
}

/*
>>>>>>> eab714463fcc844a360846d49dffd7b8c32f6f04
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
<<<<<<< HEAD
	char		*target;
=======
	char	*target;
>>>>>>> eab714463fcc844a360846d49dffd7b8c32f6f04

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
<<<<<<< HEAD
	char		*buf;
	char		*target;
=======
	char	*buf;
	char	*target;
>>>>>>> eab714463fcc844a360846d49dffd7b8c32f6f04

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
		target = ft_strjoin("/", buf);
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
<<<<<<< HEAD
	char		*target;
	int			i;
=======
	char	*target;
	int		i;
>>>>>>> eab714463fcc844a360846d49dffd7b8c32f6f04

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
