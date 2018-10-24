/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arrows.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 17:44:23 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 17:51:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

/*
** Goes one line down.
*/

void		ac_down_key(t_navig *info, t_slct *slct)
{
	int		rows;
	t_slct	*tmp;
	int		val;

	rows = get_row_number(info);
	if (slct_current(slct, info))
		return ;
	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			erase_prev(info);
			val = tmp->index % (info->x_size / (info->max_len + 2));
			tmp->current = 0;
			tmp = tmp->next == slct ? tmp->next->next : tmp->next;
			while (tmp->index % (info->x_size / (info->max_len + 2)) != val)
				tmp = tmp->next == slct ? tmp->next->next : tmp->next;
			tmp->current = 1;
			add_slct(tmp, info);
			return ;
		}
		tmp = tmp->next;
	}
}

/*
** Goes one line up.
*/

void		ac_up_key(t_navig *info, t_slct *slct)
{
	int		rows;
	t_slct	*tmp;
	int		val;

	rows = get_row_number(info);
	if (slct_current(slct, info))
		return ;
	tmp = ac_last_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			erase_prev(info);
			val = tmp->index % (info->x_size / (info->max_len + 2));
			tmp->current = 0;
			tmp = tmp->prev == slct ? tmp->prev->prev : tmp->prev;
			while (tmp->index % (info->x_size / (info->max_len + 2)) != val)
				tmp = tmp->prev == slct ? tmp->prev->prev : tmp->prev;
			tmp->current = 1;
			add_slct(tmp, info);
			return ;
		}
		tmp = tmp->prev;
	}
}

/*
** Goes to the next element.
*/

void		ac_tab_key(t_navig *info, t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	if (slct_current(slct, info))
		return ;
	while (tmp != slct)
	{
		if (tmp->current)
		{
			erase_prev(info);
			tmp->current = 0;
			if (tmp->next == slct)
			{
				tmp->next->next->current = 1;
				add_slct(tmp->next->next, info);
			}
			else
			{
				tmp->next->current = 1;
				add_slct(tmp->next, info);
			}
			return ;
		}
		tmp = tmp->next;
	}
}
