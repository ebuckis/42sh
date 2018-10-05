/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_separator.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:23:23 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 17:05:38 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static void	ft_win_line(t_parse *p)
{
	p->len += 2;
	p->str = ft_realloc(p->str, p->len);
	p->ident = ft_realloc(p->ident, p->len);
	ft_add_space(p);
}

/*
** on gagne quelques lignes
*/

/*
** On realloue de la memoire pour ajouter des espaces au cas ou
** la redirection ne soit par marquée par des espaces
*/

int			ft_separator(t_parse *p, int tmp)
{
	int		j;

	j = 0;
	if (tmp == -1)
		return (tmp);
	ft_win_line(p);
	while (j < tmp)
	{
		ft_end_while(p, p->tmp_id);
		j++;
	}
	j = p->i - 1;
	while (ft_is_white(p->s[p->i]))
		p->i++;
	if ((ft_is_red(p->s[j]) || p->s[j] == '|') &&
		(ft_is_redirection(p->s[p->i]) || !p->s[p->i]))
		return (-1);
	if (p->s[j] == ';' && ft_is_redirection(p->s[p->i]))
		return (-1);
	ft_add_space(p);
	return (1);
}
