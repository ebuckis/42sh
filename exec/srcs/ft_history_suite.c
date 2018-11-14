/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_suite.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 14:10:29 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 13:15:20 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

static int	histo_a(void)
{
	t_hist	*his;

	his = ft_close_hist(GET_HIST, NULL);
	if (his == NULL)
		return (0);
	his = ft_close_hist(CLOSE_HIST, NULL);
	return (0);
}

static int	histo_n(void)
{
	return (0);
}

int			histo_suite(t_opt_h *h)
{
	int		ret;

	ret = 0;
	printf("HISTORIQUE SUITE\n");
	if (h->d == 1)
		delete_line_history(h->offset);
	if (h->c == 1)
		delete_history();
	else if(h->a == 1)
		ret = histo_a();
	else if(h->n == 1)
		ret = histo_n();
	else
		history_invalid(h->filename, 2);
	return (ret);
}