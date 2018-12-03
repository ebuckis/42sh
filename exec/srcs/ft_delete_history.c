/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delete_history.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 13:57:57 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 11:04:16 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Reindex les id de l'historique
*/

static int	reset_index(t_hist **h)
{
	int		i;

	i = 0;
	while ((*h)->next)
		*h = (*h)->next;
	while ((*h)->prev)
	{
		if ((*h)->id != -1)
			(*h)->id = i;
		i++;
		*h = (*h)->prev;
	}
	ft_add_hist(NULL, 1, i);
	return (0);
}

/*
**	Delete maillon
*/

static int	delete_line_h(t_hist **h, int id, t_hist *del)
{
	while (*h)
	{
		if ((*h)->id == id)
		{
			del = *h;
			*h = (*h)->prev;
			if (id == 0)
			{
				ft_strdel(&del->str);
				free(del);
				(*h)->next = NULL;
			}
			else
			{
				(*h)->next = del->next;
				*h = (*h)->next;
				(*h)->prev = del->prev;
				free(del);
			}
			reset_index(h);
			return (0);
		}
		*h = (*h)->next;
	}
	return (1);
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
	{
		ft_free_hist(&(h->next));
		ft_add_hist(NULL, 1, 0);
	}
	return (0);
}

/*
**	Delete an line of history
*/

int			delete_line_history(int id)
{
	t_hist	*h;
	t_hist	*cpy;
	t_hist	*del;
	int		max;
	int		len_h;

	h = ft_close_hist(GET_HIST, NULL);
	cpy = h;
	del = NULL;
	max = info_histsize();
	len_h = cpy->next->id;
	if (id <= 0 || id > len_h || id < len_h - max)
	{
		history_out(id);
		return (1);
	}
	delete_line_h(&h, id - 1, del);
	return (0);
}
