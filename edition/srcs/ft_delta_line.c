/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delta_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 15:22:06 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:54:54 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void		ft_delta_line(t_navig *n, int nb)
{
	int		diff;
	int		a;
	int		b;

	a = nb / n->x_size;
	b = n->y_size - n->y_first;
	diff = a - b + 1;
	if (diff > 0)
	{
		n->y_first -= diff;
		n->y_start -= diff;
	}
}

/*
** calcule de delta sur y genere par le resize
*/
