/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_move_up.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 15:55:23 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:30:27 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_move_up(t_navig *n)
{
	char	*ret;

	ft_move_to_xy(n->x_len, n->y_len);
	if (!(ret = tgetstr("sf", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	ft_move_to_xy(n->x, n->y);
	return (1);
}

/*
** permet de remonter d'une ligne
*/
