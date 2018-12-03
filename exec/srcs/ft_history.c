/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:41:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 16:21:14 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Print full historique
*/

static int		ft_print_history(void)
{
	t_hist		*h;
	int			i;
	int			histsize;

	i = 0;
	h = ft_close_hist(GET_HIST, NULL);
	histsize = info_histsize();
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

int				ft_print_history_len(int nb, int i, int histsize)
{
	t_hist	*h;

	h = NULL;
	h = ft_close_hist(GET_HIST, NULL);
	histsize = info_histsize();
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
*/

int				ft_history(char **arg, char ***env)
{
	t_opt_h		*hist_opt;

	(void)env;
	if (arg == NULL)
		return (1);
	if (info_histsize() == 0)
		return (0);
	if (ft_len_tab(arg) == 1)
		return (ft_print_history());
	hist_opt = check_hist(arg);
	if (hist_opt == NULL)
		return (1);
	if (hist_opt->print_line == 1)
	{
		hist_opt = delete_struct_hist(hist_opt);
		return (0);
	}
	histo_suite(hist_opt, arg);
	hist_opt = delete_struct_hist(hist_opt);
	return (0);
}
