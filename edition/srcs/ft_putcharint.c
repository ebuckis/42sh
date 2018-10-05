/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putcharint.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 12:54:37 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:48 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int				ft_putcharint(int c)
{
	write(1, &c, 1);
	return (1);
}

/*
** fonction necessaire a l'utilisation des termcaps
*/
