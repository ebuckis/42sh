/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_suite.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 14:10:29 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 15:04:03 by yoginet     ###    #+. /#+    ###.fr     */
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

int			histo_suite(t_opt_h **h, char **arg)
{
	int		ret;

	ret = 0;
	(void)h;
	(void)arg;
	printf("HISTORIQUE SUITE\n");
	if ((*h)->c == 1)
		return (delete_history());
	else if((*h)->a == 1 || (*h)->n == 1)
		ret = histo_a();
	return (ret);
}
