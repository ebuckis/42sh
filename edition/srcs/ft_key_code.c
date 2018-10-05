/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_key_code.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 13:31:30 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:16 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_key_code(t_navig *n, char *buf)
{
	if (KEY_CODE_DEL)
	{
		if (!(ft_del_char(n)))
			return (0);
	}
	if (KEY_CODE_DIR)
	{
		if (!(ft_key_move(n, buf)))
			return (0);
	}
	else if (KEY_CODE_ALT)
	{
		if (!(ft_key_alt(n, buf)))
			return (0);
	}
	else if (IS_PRINTABLE)
	{
		if (!(ft_new_char(n, buf) && ft_move_to_xy(n->x, n->y)))
			return (0);
	}
	if (!(ft_move_to_xy(n->x, n->y)))
		return (0);
	return (1);
}

/*
** appel vers les fonctions adequates
** on move a la fin pour etre sur d'etre au bon endroit
*/
