/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_close_parse.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 11:39:36 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 14:30:39 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

void	ft_free_tab(char ***t)
{
	int		i;
	char	**tabl;

	i = 0;
	if (*t)
	{
		tabl = *t;
		while (tabl[i])
		{
			free(tabl[i]);
			tabl[i] = NULL;
			i++;
		}
		free(tabl);
		tabl = NULL;
	}
}

void	ft_free_tab3(char ***t)
{
	int		i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
	{
		ft_free_tab(&t[i]);
		i++;
	}
	free(t);
	t = NULL;
}

int		ft_close_parse(void)
{
	t_parse		**p;

	p = ft_save_struct(NULL);
	if (*p)
	{
		ft_strdel(&((*p)->s));
		ft_strdel(&((*p)->str));
		ft_strdel(&((*p)->ident));
		if ((*p)->arg)
			ft_free_tab(&((*p)->arg));
		if ((*p)->arg_id)
			ft_free_tab(&((*p)->arg_id));
		if ((*p)->hdoc)
			ft_free_tab(&((*p)->hdoc));
		if (*p)
			free(*p);
		*p = NULL;
	}
	return (1);
}

/*
** ft_close_parse peut etre appelée meme apres la sortie de la fonction
** afin de free la structure.
*/
