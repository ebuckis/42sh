/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arrows2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 17:50:15 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 17:51:09 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/autocomp.h"

static void	ac_right2(t_navig *info, t_slct *slct, t_slct *tmp)
{
	int		cols;

	cols = info->x_size / (info->max_len + 2);
	erase_prev(info);
	tmp->current = 0;
	if (tmp->index % cols != 0 && tmp->next != slct)
	{
		tmp->next->current = 1;
		add_slct(tmp->next, info);
	}
	else
	{
		while (tmp->index % cols != 1)
			tmp = tmp->prev;
		tmp->current = 1;
		add_slct(tmp, info);
	}
}

/*
** Goes one column to the right.
*/

void		ac_right_key(t_navig *info, t_slct *slct)
{
	t_slct	*tmp;

	if (slct_current(slct, info))
		return ;
	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			ac_right2(info, slct, tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	ac_left2(t_navig *info, t_slct *slct, t_slct *tmp)
{
	int		cols;
	int		rows;

	rows = get_row_number(info);
	cols = info->x_size / (info->max_len + 2);
	erase_prev(info);
	tmp->current = 0;
	if (tmp->index % cols != 1 && tmp->prev != slct)
	{
		tmp->prev->current = 1;
		add_slct(tmp->prev, info);
	}
	else
	{
		if (tmp->index % rows != 0)
			while (tmp->index % cols != 0 || tmp == slct)
				tmp = tmp->next;
		else
			while (tmp->next != slct)
				tmp = tmp->next;
		tmp->current = 1;
		add_slct(tmp, info);
	}
}

/*
** Goes one column to the left.
*/

void		ac_left_key(t_navig *info, t_slct *slct)
{
	t_slct	*tmp;

	if (slct_current(slct, info))
		return ;
	tmp = ac_last_elem(slct);
	while (tmp != slct)
	{
		if (tmp->current)
		{
			ac_left2(info, slct, tmp);
			return ;
		}
		tmp = tmp->prev;
	}
}
