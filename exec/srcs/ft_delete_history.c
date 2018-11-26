/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_delete_history.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 10:29:36 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 14:22:39 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Delete History
*/

int			delete_history(void)
{
	t_hist	*h;

	h = NULL;
	printf("%s START\n", __func__);
	h = ft_close_hist(GET_HIST, NULL);
	if (h && h->next)
		ft_free_hist(&h);
	ft_close_hist(SAVE_HIST, NULL);
	printf("%s END\n", __func__);
	printf("DELETE FILE\n");
	return (0);
}

/*
**	Delete an line of history
*/

int			delete_line_history(int id)
{
	int		max;

	max = info_histsize();
	if (id <= 0 || id > max)
		history_out(id);
	printf("DELETE LINE History : %d\n", id);
	return (0);
}
