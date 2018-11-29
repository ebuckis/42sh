/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_verif_histsize.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 13:34:49 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 13:44:03 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void	ft_verif_histsize(t_navig *n)
{
	int		i;
	t_hist	*h;

	i = 0;
	h = ft_close_hist(GET_HIST, NULL)->next;
	while (h)
	{
		if (i >= info_histsize())
		{
			ft_free_hist(&h);
			return ;
		}
		h = h->next;
		i++;
	}
}
