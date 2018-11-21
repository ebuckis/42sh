/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 20:06:23 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 20:19:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** builtin unset : supprimer une variable locale
*/

int			ft_unset(char **arg, char ***p_env)
{
	int		i;
	int		nb_double;
	char	**tmp;

	nb_double = 0;
	if (arg[1])
	{
		i = 0;
		while (arg[++i])
		{
			if (ft_doublon3(arg[i], p_env[1]))
				nb_double++;
		}
		if (nb_double)
		{
			tmp = ft_unsetenv2(arg, p_env[1], nb_double);
			ft_free_tab(&p_env[1]);
			p_env[1] = tmp;
		}
	}
	return (0);
}
