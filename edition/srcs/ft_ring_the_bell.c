/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ring_the_bell.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 12:05:01 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:52 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_ring_the_bell(void)
{
	char	*ret;

	if (!(ret = tgetstr("bl", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	return (1);
}

/*
** besoin d'explication ??
*/
