/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setenv.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 16:51:13 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:05:38 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

int			display_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
	return (0);
}

/*
** construction de env2 avec KEY=VALUE
*/

int			ft_setenv2(char **arg, char ***env)
{
	char	**env2;
	char	*tmp;
	char	**tmp2;

	env2 = (char**)malloc(sizeof(char*) * 2);
	tmp = ft_strjoin(arg[1], "=");
	env2[0] = ft_strjoin(tmp, arg[2]);
	ft_memdel((void**)&tmp);
	env2[1] = NULL;
	tmp2 = ft_mix_env(*env, env2);
	ft_free_tab(env);
	ft_free_tab(&env2);
	*env = tmp2;
	return (0);
}

/*
** mix env et env2 sans les doublons
*/

char		**ft_mix_env(char **env, char **env2)
{
	char	**arg;
	int		size_tab;
	int		i;
	int		j;
	int		k;

	size_tab = ft_tab_size(env, NULL) + ft_tab_size(env2, env);
	arg = (char**)malloc(sizeof(char*) * (size_tab + 1));
	i = 0;
	j = -1;
	while (env[++j])
	{
		if (!(ft_doublon(env[j], env2, -1)))
			arg[i++] = ft_strdup(env[j]);
	}
	j = i;
	k = i;
	while (env2[k - j])
	{
		if (!ft_doublon(env2[k - j], env2, k - j))
			arg[i++] = ft_strdup(env2[k - j]);
		k++;
	}
	arg[i] = NULL;
	return (arg);
}

/*
** built-in setenv : ajoute une variable d'env sous le format KEY VALUE
** gestion des cas d'erreurs
*/

int			ft_setenv(char **arg, char ***env)
{
	int		i;
	int		ret;

	ret = 1;
	if (!arg[1])
		ret = display_env(*env);
	else if (arg[2] && arg[3])
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (!ft_isalpha(arg[1][0]))
		ft_putendl_fd("setenv: Variable must begin with a letter.", 2);
	else
	{
		i = -1;
		while (++i < (int)ft_strlen(arg[1]))
		{
			if (!ft_isalnum(arg[1][i]))
			{
				ft_putstr_fd("setenv: Variable must contain alphanumeric ", 2);
				ft_putendl_fd("characters.", 2);
				return (ret);
			}
		}
		ret = ft_setenv2(arg, env);
	}
	return (ret);
}
