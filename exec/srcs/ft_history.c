/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:41:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 14:20:51 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Print Usage
*/

static void	history_usage(char *err)
{
	if (err != NULL)
	{
		if (ft_atoi(err) == 0)
			return ;
	}
	if (err == NULL)
		ft_printf("42sh: History:\n");
	else
		ft_printf("42sh: History: %s\n", err);
	ft_printf("history: usage: history [-c] [-d offset] [n] or ");
	ft_printf("history -awrn [filename] or history -ps [arg...]\n");
}

/*
**	Print full historique
*/

static int	ft_print_history(int histsize)
{
	t_hist		*h;
	int			i;

	i = 0;
	h = ft_close_hist(GET_HIST, NULL);
	if (h == NULL)
		return (1);
	while (h->next && histsize != 0)
	{
		h = h->next;
		i++;
		histsize--;
	}
	while (i != 0)
	{
		ft_printf("  %d\t%s\n", h->id + 1, h->str);
		i--;
		h = h->prev;
	}
	return (0);
}

/*
** Print end historique (max -> nb)
*/

static int	ft_print_history_len(int nb, int histsize)
{
	t_hist	*h;
	int		i;

	h = NULL;
	i = 0;
	h = ft_close_hist(GET_HIST, NULL);
	if (h == NULL)
		return (1);
	if (nb <= 0)
		return (0);
	while (h->next && i < nb && histsize != 0)
	{
		h = h->next;
		i++;
	}
	while (nb != 0 && h)
	{
		if (h->id != -1)
		{
			ft_printf("  %d\t%s\n", h->id + 1, h->str);
			nb--;
		}
		h = h->prev;
		histsize--;
	}
	return (0);
}

/*
**	Core History
**	HISTSIZE a aller recuperer dans les variables set
*/

int			ft_history(char **arg, char ***env)
{
	t_opt_h	*hist_opt;

	(void)env;
	hist_opt = check_hist(arg);
	if (hist_opt == NULL)
		return (1);
	if (len == 1)
		return (ft_print_history(histsize));
	else if (len == 2 && ft_atoi(arg[1]) != 0)
		return (ft_print_history_len(ft_atoi(arg[1]), histsize));
	else if (ft_strcmp(arg[1], "-c") == 0)
		ft_printf("clear History\n");
	else if (ft_strcmp(arg[1], "-d") == 0)
		ft_printf("clear History offset\n");
	else
		history_usage(arg[1]);
	return (0);
}
