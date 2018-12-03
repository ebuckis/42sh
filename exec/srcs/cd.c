/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/06 10:44:16 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 13:18:45 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
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
**  Mise a jour du PWD et OLDPWD in env
*/

static int		actualise_env(char *new_pwd, char ***p_env)
{
	char		*pwd;
	char		*tmp;

	pwd = NULL;
	tmp = ft_strnew(255);
	getcwd(tmp, 255);
	pwd = ft_getpwd(*p_env, 0);
	if (new_pwd)
	{
		if (new_pwd[0] == '/')
			ft_setpwd(*p_env, 0, new_pwd);
		else
			ft_setpwd(*p_env, 0, tmp);
	}
	if (pwd)
		ft_setpwd(*p_env, 1, pwd);
	ft_strdel(&pwd);
	ft_strdel(&tmp);
	return (0);
}

/*
** gestion du cd -, des paths absolus et relatifs et des erreurs
*/

int				ft_putendl_fd_arg(char *str, char *path)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

/*
** built-in cd
*/

static int		check_target(char **target, char ***p_env)
{
	if (*target)
	{
		if (ft_strcmp(*target, "cd") == 0)
		{
			ft_strdel(target);
			*target = ft_home(*p_env);
			if (*target == NULL)
				ft_putendl_fd("cd: HOME not set", 2);
		}
		else if (ft_strcmp(*target, "oldpwd") == 0)
		{
			ft_strdel(target);
			*target = ft_getpwd(*p_env, 1);
			if (*target == NULL)
				ft_putendl_fd("cd: OLDPWD not set", 2);
		}
	}
	return (0);
}

int				ft_cd(char **arg, char ***p_env)
{
	char		*target;
	int			p;

	target = NULL;
	p = 0;
	if (arg[1] == NULL)
		target = ft_home(*p_env);
	else
		target = ret_target(arg, 0, p, 0);
	check_target(&target, p_env);
	if (target == NULL)
		return (1);
	if (chdir(target) < 0)
	{
		ft_putstr_fd("cd : an error is occured\n", 2);
		ft_strdel(&target);
		return (1);
	}
	actualise_env(target, p_env);
	ft_strdel(&target);
	return (0);
}
