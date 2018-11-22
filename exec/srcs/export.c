/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   export.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 20:09:29 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 12:16:08 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** built-in export : exporte une variable locale (p_env[1]) 
** si elle est presente vers l'env (p_env[0])
*/

int			ft_export(char **arg, char ***p_env)
{
	char	*val;
	int		i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] && (val = get_value(p_env, arg[i], 1, 1)))
		{
			printf("%s\n", val);
			ft_memdel((void**)&val);
		}
	}
	return (0);
}
