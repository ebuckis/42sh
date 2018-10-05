/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_size.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 15:49:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:01 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int					ft_get_size(int *x, int *y)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) == -1)
		return (0);
	*y = w.ws_row;
	*x = w.ws_col;
	return (1);
}

/*
** permet d'obtenir la taile de la window
*/
