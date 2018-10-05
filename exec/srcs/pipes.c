/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipes.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 11:15:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 15:37:48 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** cree un tableau avec les indices de debut de commande entre chaque pipe
*/

static int			*create_tab_pipe(t_parse *p, int i, int nb_pipe,
		int *tab_pipe)
{
	int		j;

	tab_pipe = (int*)malloc(sizeof(int) * (nb_pipe + 2));
	tab_pipe[0] = i;
	j = 1;
	while (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
	{
		if (ft_strchr(p->arg_id[i], PIPE))
			tab_pipe[j++] = ++i;
		else
			i++;
	}
	tab_pipe[j] = -1;
	return (tab_pipe);
}

/*
** cree un tableau avec les indices de debut de pipe puis appel fork_shell
** s'arrete si il y a un ";", erreur si 2 pipes colles ou pipe au ddbut ou a
** la fin sans argument
*/

void				ft_manage_pipe(t_parse *p, int begin, char ***p_env)
{
	int		i;
	int		nb_pipe;
	int		*tab_pipe;

	i = begin;
	nb_pipe = 0;
	tab_pipe = NULL;
	if (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
	{
		while (p->arg[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
		{
			if (ft_strchr(p->arg_id[i], PIPE))
			{
				if (i == begin || ft_strchr(p->arg_id[i - 1], PIPE) ||
					!p->arg[i + 1] || ft_strchr(p->arg_id[i + 1], SEMICOLON))
					return (ft_putendl_fd("parse error", 2));
				else
					nb_pipe++;
			}
			i++;
		}
		tab_pipe = create_tab_pipe(p, begin, nb_pipe, tab_pipe);
		ft_fork_shell(p, tab_pipe, p_env, nb_pipe);
		ft_memdel((void**)&tab_pipe);
	}
}
