/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 10:50:52 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 15:43:52 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** chdir change le current working directory puis on met a jour PWD et OLDPWD
** dans les variables d'env
*/

static int		ft_cd3(char ***p_env, char *pwd, char *oldpwd)
{
	char	buf[1000];

	chdir(pwd);
	ft_setpwd(*p_env, 0, getcwd(buf, 1000));
	ft_setpwd(*p_env, 1, oldpwd);
	return (0);
}

/*
** gestion du cd -, des paths absolus et relatifs et des erreurs
*/

void			ft_putendl_fd_arg(char *str, char *path)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

static int		ft_cd2(char ***p_env, char *pwd, char *oldpwd, char **arg)
{
	struct stat		buf;
	char			*mem;
	char			*path;
	int				ret;

	ret = 1;
	if (ft_strequ(arg[1], "-"))
		ret = ft_cd3(p_env, oldpwd, pwd);
	else
	{
		mem = ft_strjoin(pwd, "/");
		path = (arg[1][0] == '/') ? ft_strdup(arg[1]) : ft_strjoin(mem, arg[1]);
		ft_memdel((void**)&mem);
		if (stat(path, &buf) != 0)
			ft_putendl_fd_arg("cd: no such file or directory: ", path);
		else if (!(buf.st_mode & S_IFDIR) || (buf.st_mode & S_IFCHR))
			ft_putendl_fd_arg("cd: not a directory: ", path);
		else if (access(path, X_OK))
			ft_putendl_fd_arg("cd: permission denied: ", path);
		else
			ret = ft_cd3(p_env, path, pwd);
		ft_memdel((void**)&path);
	}
	return (ret);
}

/*
** built-in cd, on recupere les 3 variables d'env PWD, OLDPWD, HOME
*/

int				ft_cd(char **arg, char ***p_env)
{
	char			*home;
	char			*pwd;
	char			*oldpwd;
	int				ret;

	ret = 1;
	home = ft_home(*p_env);
	pwd = ft_getpwd(*p_env, 0);
	oldpwd = ft_getpwd(*p_env, 1);
	if (!arg[1])
		if (home)
			ret = ft_cd3(p_env, home, pwd);
		else
			ft_putendl_fd("cd: HOME not set", 2);
	else if (!arg[2])
		ret = ft_cd2(p_env, pwd, oldpwd, arg);
	else
		ft_putendl_fd("cd: too many arguments", 2);
	ft_memdel((void**)&home);
	ft_memdel((void**)&pwd);
	ft_memdel((void**)&oldpwd);
	return (ret);
}
