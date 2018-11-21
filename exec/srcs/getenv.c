/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getenv.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 09:21:41 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 13:31:08 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** retourne l'env au lancement d'un programme
*/

char		***ft_getenv(int argc, char *argv[], char *env[])
{
	int		i;
	char	***myenv;

	if (!(myenv = (char***)malloc(sizeof(char**) * 2)) || argc < 0 || argv < 0)
		return (NULL);
	myenv[0] = NULL;
	myenv[1] = NULL;
	if (!env)
		return (myenv);
	i = -1;
	while (env[++i])
		;
	if (!(myenv[0] = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		myenv[0][i] = ft_strdup(env[i]);
	myenv[0][i] = NULL;
	i = -1;
	return (myenv);
}

/*
** retourne la variable HOME
*/

char		*ft_home(char **env)
{
	int		i;
	char	*home;

	i = -1;
	if (env)
	{
		while (env[++i])
		{
			if ((home = ft_strstr(env[i], "HOME=")))
				return (ft_strdup(home + 5));
		}
	}
	return (NULL);
}

/*
** retourne la variable PWD ou OLDPWD
*/

char		*ft_getpwd(char **env, int old)
{
	int		i;
	char	*pwd;

	i = -1;
	if (env)
	{
		while (env[++i])
		{
			if (old == 0)
			{
				if ((pwd = ft_strstr(env[i], "PWD=")) &&
					!ft_strstr(env[i], "OLDPWD="))
					return (ft_strdup(pwd + 4));
			}
			else
			{
				if ((pwd = ft_strstr(env[i], "OLDPWD=")))
					return (ft_strdup(pwd + 7));
			}
		}
	}
	return (NULL);
}

/*
** set la variable PWD ou OLDPWD
*/

void		ft_setpwd(char **env, int old, char *pwd)
{
	int		i;

	i = -1;
	if (env)
	{
		while (env[++i])
		{
			if (old == 0)
			{
				if (ft_strstr(env[i], "PWD=") && !ft_strstr(env[i], "OLDPWD="))
				{
					ft_memdel((void **)&env[i]);
					env[i] = ft_strjoin("PWD=", pwd);
				}
			}
			else
			{
				if (ft_strstr(env[i], "OLDPWD="))
				{
					ft_memdel((void **)&env[i]);
					env[i] = ft_strjoin("OLDPWD=", pwd);
				}
			}
		}
	}
}
