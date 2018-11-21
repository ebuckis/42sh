/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   equal.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 14:50:43 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 16:15:14 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** 
*/

static int			ft_setenvloc2(char *str, char ***p_env)
{
	char	**env2;
	char	**tmp;

	if (!(env2 = (char**)malloc(sizeof(char*) * 2)))
		return(1);
	env2[0] = ft_strdup(str);
	env2[1] = NULL;
	tmp = ft_mix_env(p_env[1], env2);
	ft_free_tab(&p_env[1]);
	ft_free_tab(&env2);
	p_env[1] = tmp;
	return (0);
}

/*
* built-in equal : si presence de = dans arg , il faut au moins un char avant
** il peut ne rien avoir apres le egal
** a stocker dans p_env[1] (partie var locale)
** il peut y avoir plusieurs arg susccessif avec =
** la fin des arguments est traite comme une commande normale via env
*/

int			ft_equal(char **arg, char ***p_env)
{
	int		i;
	int		ret;

	ret = 1;
	i = -1;
	while (arg[++i] && ft_strchr(arg[i], '='))
	{
		if (!ft_isalpha(arg[i][0]))
		{
			ft_putendl_fd("setenv: Variable must begin with a letter.", 2);
			return (ret);
		}
		ret = ft_setenvloc2(arg[i], p_env);
	}
	if (arg[i])
		;
	//env du reste
	ft_printf("debug display var local\n");
	display_env(p_env[1]);
	return (ret);
}
