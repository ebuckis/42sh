/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_info.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 12:07:02 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 16:49:27 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

/*
** Gets various informations such as the longest word in the list and the
** number of elements.
*/

void	ac_get_info(t_slct *slct, t_navig *info)
{
	t_slct	*tmp;

	tmp = NULL;
	if (slct)
	{
		tmp = ac_first_elem(slct);
		while (tmp != slct)
		{
			if (tmp->len > info->max_len)
				info->max_len = tmp->len;
			info->nb_elem++;
			tmp = tmp->next;
		}
	}
}
