/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   and_or.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 13:56:31 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 15:50:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** cree un tableau avec les indices de debut de commande entre chaque && ||
*/

static int			*create_tab_and_or(t_parse *p, int i, int nb_and_or,
		int *tab_and_or)
{
	int		j;

	tab_and_or = (int*)malloc(sizeof(int) * (nb_and_or + 2));
	tab_and_or[0] = i;
	j = 1;
	while (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
	{
		if (ft_strchr(p->arg_id[i], OR) || ft_strchr(p->arg_id[i], AND))
			tab_and_or[j++] = ++i;
		else
			i++;
	}
	tab_and_or[j] = -1;
	return (tab_and_or);
}

/*
** gere si les commandes suivantes doivent etre executer en fonction de && ||
** et des valeurs de retour des commandes precedentes
*/

static void			ft_manage_and_or_2(t_parse *p, int *tab_and_or,
	char ***p_env)
{
	int	i;

	i = -1;
	while (tab_and_or[++i] >= 0)
	{
		if (i == 0 ||
			(ft_strchr(p->arg_id[tab_and_or[i] - 1], AND) && p->ret == 0) ||
			(ft_strchr(p->arg_id[tab_and_or[i] - 1], OR) && p->ret > 0))
			ft_manage_pipe(p, tab_and_or[i], p_env);
	}
}

/*
** cree un tableau avec les indices de debut de && || puis appel manage pipe
** s'arrete si il y a un ";", erreur si 2 c && || colles ou && || au debut ou
** a la fin sans argument
*/

void				ft_manage_and_or(t_parse *p, int begin, char ***p_env)
{
	int		i;
	int		nb_and_or;
	int		*tab_and_or;

	i = begin;
	nb_and_or = 0;
	tab_and_or = NULL;
	if (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
	{
		while (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
		{
			if (ft_strchr(p->arg_id[i], AND) || ft_strchr(p->arg_id[i], OR))
			{
				if (i == begin || ft_strchr(p->arg_id[i - 1], OR) ||
					ft_strchr(p->arg_id[i - 1], AND) || !p->arg[i + 1] ||
					ft_strchr(p->arg_id[i + 1], SEMICOLON))
					return (ft_putendl_fd("parse error", 2));
				nb_and_or++;
			}
			i++;
		}
		tab_and_or = create_tab_and_or(p, begin, nb_and_or, tab_and_or);
		ft_manage_and_or_2(p, tab_and_or, p_env);
		ft_memdel((void**)&tab_and_or);
	}
}
