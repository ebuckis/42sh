/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_goto_i_from_end.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 18:08:03 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:04 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void		ft_goto_i_from_end(t_navig *n)
{
	int		j;
	int		i_bis;

	i_bis = n->i;
	j = ft_strlen(n->s);
	while (j > i_bis)
	{
		ft_x_change(n, MOVE_LEFT);
		n->i++;
		j--;
	}
	ft_move_to_xy(n->x, n->y);
	n->i = i_bis;
}

/*
** on va jusqu'a la fin et on se repositionne sur i
*/
