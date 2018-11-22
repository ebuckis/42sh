/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   export.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 20:09:29 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 13:15:42 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** built-in export : exporte une variable locale (p_env[1])
** si elle est presente vers l'env (p_env[0]) en l'ecrasant si elle existe deja
*/

int			ft_export(char **arg, char ***p_env)
{
	char	*val;
	int		i;
	char	**env2;
	char	*tmp;
	char	**tmp2;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] && (val = get_value(p_env, arg[i], 1, 1)))
		{
			printf("%s\n", val);
			env2 = (char**)malloc(sizeof(char*) * 2);
			tmp = ft_strjoin(arg[i], "=");
			env2[0] = ft_strjoin(tmp, val);
			ft_memdel((void**)&tmp);
			ft_memdel((void**)&val);
			env2[1] = NULL;
			tmp2 = ft_mix_env(p_env[0], env2);
			ft_free_tab(&p_env[0]);
			ft_free_tab(&env2);
			p_env[0] = tmp2;
		}
	}
	return (0);
}
