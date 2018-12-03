/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_suite2.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 12:49:21 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 15:51:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Print arg et ne save pas la ligne dans l'historique
*/

int			histo_p(t_opt_h *h, char **arg)
{
	int		i;
	t_hist	*hi;

	i = 1;
	(void)h;
	hi = ft_close_hist(GET_HIST, NULL);
	while (arg[i])
	{
		if (arg[i] == NULL)
			return (0);
		if (arg[i][0] == '-')
			;
		else
			ft_putendl(arg[i]);
		i++;
	}
	delete_line_history(-100);
	return (0);
}

/*
**	Insert les arguments sur une seul line dans l'historique
*/

static int	ft_add_arg(char **tmp, char *str)
{
	char	*tmp2;
	char	*cpy;

	tmp2 = NULL;
	cpy = NULL;
	if (*tmp == NULL)
	{
		*tmp = ft_strdup(str);
		return (0);
	}
	cpy = ft_strdup(*tmp);
	tmp2 = ft_strjoin(" ", str);
	ft_strdel(tmp);
	*tmp = ft_strjoin(cpy, tmp2);
	ft_strdel(&cpy);
	ft_strdel(&tmp2);
	return (0);
}

static char	*ft_string_arg(char **arg)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	tmp = NULL;
	tmp2 = NULL;
	while (arg[i])
	{
		if (arg[i] == NULL)
			return (tmp);
		else if (arg[i][0] == '-')
			;
		else
			ft_add_arg(&tmp, arg[i]);
		i++;
	}
	return (tmp);
}

int			histo_s(t_opt_h *h, char **arg)
{
	t_hist		*his;
	char		*tmp;

	his = NULL;
	tmp = NULL;
	(void)h;
	his = ft_close_hist(GET_HIST, NULL);
	tmp = ft_string_arg(arg);
	if (his == NULL || tmp == NULL)
	{
		ft_strdel(&tmp);
		return (0);
	}
	his = his->next;
	ft_strdel(&his->str);
	his->str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (0);
}
