/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_verif_histsize.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 13:34:49 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 11:21:07 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"
#include "../../exec/includes/exec.h"

void	ft_verif_histsize(void)
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
		if (i >= info_histsize())
		{
			tmp = h->prev;
			ft_free_hist(&h);
			tmp->next = NULL;
			return ;
		}
		h = h->next;
		i++;
	}
}
