/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_verif_term_size.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 18:26:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:37:45 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_verif_term_size(t_navig *n)
{
	int		nb;

	nb = ft_strlen(n->prompt) + ft_strlen(n->s) + 1;
	if (nb == n->y_size * n->x_size)
		return (0);
	if (nb > n->y_size * n->x_size)
		return (-1);
	return (1);
}

/*
** permet de verifier la taille du terminal par rapport a la longueur de s
** et de celle du prompt
*/
