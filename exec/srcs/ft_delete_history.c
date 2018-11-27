/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delete_history.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 13:57:57 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 16:51:02 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Delete maillon
*/

int			delete_line_h(t_hist **h, int id)
{
	t_hist	*del;

	del = NULL;
	while (*h)
	{
		if ((*h)->id == id)
		{
			del = *h;
			*h = (*h)->prev;
			(*h)->next = del->next;
			*h = (*h)->next;
			(*h)->prev = del->prev;
			free(del);
			return (0);
		}
		*h = (*h)->next;
	}
	return (0);
}

/*
**	Delete History
**	Ne suprime rien dans le fichier .bash_history (sauf a la fermeture du shell)
*/

int			delete_history(void)
{
	t_hist	*h;

	h = NULL;
	h = ft_close_hist(GET_HIST, NULL);
	if (h && h->next)
		ft_free_hist(&(h->next));
	return (0);
}

/*
**	Delete an line of history
*/

int			delete_line_history(int id)
{
	t_hist	*h;
	t_hist	*cpy;
	int		max;
	int		len_h;

	h = ft_close_hist(GET_HIST, NULL);
	cpy = h;
	max = info_histsize();
	len_h = cpy->next->id;
	if (id <= 0 || id > len_h || id < len_h - max)
	{
		history_out(id);
		return (1);
	}
	delete_line_h(&h, id - 1);
	return (0);
}
