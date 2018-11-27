/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_give_hist.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 16:27:53 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 13:16:48 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static t_hist	*ft_loop_hist(t_hist *h, int id)
{
	while (id && h)
	{
		h = h->next;
		id--;
	}
	return (h);
}

char	*ft_give_hist(int i, int id)
{
	t_hist	*h = NULL;

	h = ft_close_hist(GET_HIST, NULL);
	h = ft_loop_hist(h, id);
	if (!h)
		return (NULL);
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

/*
** TODO: var static a remettre a zero
*/