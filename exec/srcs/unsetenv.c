/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unsetenv.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 15:06:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:12:17 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

static int	ft_doublon3(char *line, char **arg)
{
	int		i;
	char	*p;
	char	*tmp;

	i = -1;
	if (arg)
	{
		while (arg[++i])
		{
			p = ft_strchr(arg[i], '=');
			if (p && ft_strequ((tmp = ft_strsub(arg[i], 0, p - arg[i])), line))
			{
				ft_memdel((void**)&tmp);
				return (1);
			}
			if (tmp)
				ft_memdel((void**)&tmp);
		}
	}
	return (0);
}

static int	ft_doublon2(char *line, char **arg)
{
	int		i;
	char	*p;
	char	*tmp;

	i = 0;
	if (arg)
	{
		while (arg[++i])
		{
			p = ft_strchr(line, '=');
			if (p && ft_strequ((tmp = ft_strsub(line, 0, p - line)), arg[i]))
			{
				ft_memdel((void**)&tmp);
				return (1);
			}
			if (tmp)
				ft_memdel((void**)&tmp);
		}
	}
	return (0);
}

static int	ft_tab_size2(char **arg)
{
	int		i;

	i = -1;
	if (arg)
	{
		while (arg[++i])
			;
		return (i);
	}
	return (0);
}

/*
** cree un nouveau tableau env2 avec la var en moins
*/

static char	**ft_unsetenv2(char **arg, char **env, int nb_double)
{
	char	**env2;
	int		i;
	int		j;

	env2 = (char**)malloc(sizeof(char*) *
		(ft_tab_size2(env) - nb_double + 1));
	i = 0;
	j = i;
	while (env[i])
	{
		if (ft_doublon2(env[i], arg))
			i++;
		else
		{
			env2[j] = ft_strdup(env[i]);
			j++;
			i++;
		}
	}
	env2[j] = NULL;
	return (env2);
}

/*
** builtin unsetenv : supprimer une variable d'env
*/

int			ft_unsetenv(char **arg, char ***env)
{
	int		i;
	int		nb_double;
	char	**tmp;

	nb_double = 0;
	if (!arg[1])
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
	{
		i = 0;
		while (arg[++i])
		{
			if (ft_doublon3(arg[i], *env))
				nb_double++;
		}
		if (nb_double)
		{
			tmp = ft_unsetenv2(arg, *env, nb_double);
			ft_free_tab(env);
			*env = tmp;
		}
	}
	return ((!arg[1]) ? 1 : 0);
}
