/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_give_hist.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 16:27:53 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:55:02 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

char	*ft_give_hist(int i, t_hist *list)
{
	static t_hist	*h = NULL;

	if (i == 0)
		h = list;
	else if (i == 1 && h->next)
		h = h->next;
	else if (i == -1 && h->prev)
		h = h->prev;
	else
		return (NULL);
	return (h->str);
}

/*
** i == 0 -> save de l'hist
** i == 1 && il y a un maillon apres -> next
** i == -1 && il y a un maillon avant -> prev
** sinon on NULL
** et on revoie le char * correspondant a l'historique demandé
*/
