/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_give_hist.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 16:27:53 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/22 17:30:49 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

char	*ft_give_hist(int i, t_hist *list)
{
	static t_hist	*h = NULL;

	if (i == SAVE_HIST)
		h = list;
	else if (i == NEXT_HIST && h->next)
		h = h->next;
	else if (i == PREV_HIST && h->prev)
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
