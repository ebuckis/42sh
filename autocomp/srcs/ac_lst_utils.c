/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 14:10:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 11:55:12 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

void	ac_add_after_lst(t_slct *elem, struct dirent *dp)
{
	t_slct	*new_elem;

	new_elem = NULL;
	if ((new_elem = (t_slct*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = ft_strdup(dp->d_name);
		while (add_bs(new_elem->name))
			add_bs_in_str(&new_elem->name);
		new_elem->len = ft_strlen(new_elem->name);
		new_elem->is_exe = is_exe(new_elem->name);
		new_elem->is_dir = dp->d_type == DT_DIR ? 1 : 0;
		if (new_elem->is_dir || new_elem->is_exe)
			new_elem->len++;
		new_elem->current = 0;
		new_elem->index = 0;
		new_elem->prev = elem;
		new_elem->next = elem->next;
		elem->next->prev = new_elem;
		elem->next = new_elem;
	}
}

void	ac_add_before_lst(t_slct *elem, struct dirent *dp)
{
	t_slct	*new_elem;
	int		i;

	new_elem = NULL;
	if ((new_elem = (t_slct*)malloc(sizeof(*new_elem))))
	{
		new_elem->name = ft_strdup(dp->d_name);
		while (add_bs(new_elem->name))
			add_bs_in_str(&new_elem->name);
		new_elem->len = ft_strlen(new_elem->name);
		i = is_exe(new_elem->name);
		new_elem->is_exe = i;
		new_elem->is_dir = dp->d_type == DT_DIR ? 1 : 0;
		if (new_elem->is_dir || new_elem->is_exe)
			new_elem->len++;
		new_elem->current = 0;
		new_elem->index = 0;
		new_elem->prev = elem->prev;
		new_elem->next = elem;
		elem->prev->next = new_elem;
		elem->prev = new_elem;
	}
}

/*
** Adds an element at the beginning of the linked list
*/

void	ac_add_queue(t_slct *root, struct dirent *dp)
{
	ac_add_before_lst(root, dp);
}

/*
** Adds an element at the end of the linked list
*/

void	ac_add_head(t_slct *root, struct dirent *dp)
{
	ac_add_after_lst(root, dp);
}

/*
** Removes an element from the linked list
*/

void	ac_remove_elem(t_slct *elem)
{
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	ft_strdel(&elem->name);
}
