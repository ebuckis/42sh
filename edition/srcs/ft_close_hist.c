/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_close_hist.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 16:32:16 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 13:16:11 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void				ft_free_hist(t_hist **h)
{
	if (!h || !*h)
		return ;
	ft_free_hist(&((*h)->next));
	if ((*h)->str)
		ft_strdel(&((*h)->str));
	(*h)->prev = NULL;
	free(*h);
	*h = NULL;
}

t_hist				*ft_close_hist(int i, t_hist *list)
{
	static t_hist	*h = NULL;

	if (i == SAVE_HIST)
		h = list;
	else if (i == CLOSE_HIST)
	{
		ft_list_to_file();
		ft_free_hist(&h);
		ft_copy_paste(NULL, NULL, 1);
	}
	else if (i == GET_HIST)
		return (h);
	return (NULL);
}

/*
** ft_close enregistre l'historique quand i == 0
** redonne l'hist
** et free l'hist
*/
