/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_push_enter.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 13:55:34 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:35:30 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_push_enter(t_navig *n)
{
	char		*tmp;

	if (!(ft_move_to_xy(n->x_len, n->y_len)))
		return (0);
	ft_putstr("\n");
	if (!n->s)
		return (0);
	if (n->s && (tmp = ft_whitespace(n->s)))
	{
		free(tmp);
		if (!(ft_add_hist(n->s)))
			return (0);
	}
	else if (n->s)
	{
		ft_strdel(&(n->s));
		return (0);
	}
	return (1);
}

/*
** appelée quand on appui sur entrée
** on move a la fin de la string, et o effectue un retour a la ligne
** si on a 'rien' dans la string on revoit NULL en char *
** sinon on l'ajoute a l'historique
** le dernier else if est dans le cas ou s existe mais qu'il ne contient que
** des espaces
*/
