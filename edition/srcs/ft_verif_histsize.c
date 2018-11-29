/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_verif_histsize.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 13:34:49 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 14:27:18 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"
#include "../../exec/includes/exec.h"

void	ft_verif_histsize()
{
	int		i;
	t_hist	*h;
	t_hist	*tmp;

	i = 0;
	h = ft_close_hist(GET_HIST, NULL);
	if (!h || !h->next)
		return ;
	h = h->next;
	while (h)
	{
		dprintf(2, "boucle %d avec max = %d\n", i, info_histsize());
		if (i >= info_histsize())
		{
			tmp = h->prev;
			dprintf(2, "%s\n", h->str);
			ft_free_hist(&h);
			tmp->next = NULL;
			return ;
		}
		h = h->next;
		i++;
	}
}
