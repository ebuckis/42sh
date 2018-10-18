/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 13:57:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 17:13:35 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

/*
** Creates the neutral element of the
** linked list, that is its beginning and
** ending, and returns it.
*/

t_slct	*root_slct(void)
{
	t_slct	*lst;

	lst = NULL;
	if (!(lst = malloc(sizeof(*lst))))
		return (NULL);
	lst->current = 1;
	lst->len = 0;
	lst->index = 0;
	lst->is_dir = 0;
	lst->name = NULL;
	lst->next = lst;
	lst->prev = lst;
	return (lst);
}

/*
** Returns the first element of the linked list.
*/

t_slct	*ac_first_elem(t_slct *root)
{
	if (root->next != root)
		return (root->next);
	else
		return (NULL);
}

/*
** Returns the last element of the linked list.
*/

t_slct	*ac_last_elem(t_slct *root)
{
	if (root->prev != root)
		return (root->prev);
	else
		return (NULL);
}

void	update_index(t_slct *root)
{
	t_slct	*tmp;

	tmp = ac_first_elem(root);
	while (tmp != root)
	{
		tmp->index = tmp->prev->index + 1;
		tmp = tmp->next;
	}
}
