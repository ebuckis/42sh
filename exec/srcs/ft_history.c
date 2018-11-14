/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:41:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 15:52:21 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	delete_hist
*/
/*
int				delete_line_history(t_opt_h **h, char **arg, int j, int i)
{
	char	*tmp;
	int		pos;

	tmp = NULL;
	// a gerer :
	// si history -d 5-c
	// --> return error
	if (i + 1 >= (int)ft_strlen(arg[j]) && arg[j + 1] == NULL)
	{
		ft_putstr_fd("42sh: history: -d: option requires an arguments\n", 2);
		history_usage();
		return (1);
	}
	tmp = ft_strsub(arg[j], i + 1, ft_strlen(arg[j]) - i + 1);
	pos = ft_atoi(tmp);
	ft_strdel(&tmp);
	if (pos == 0 && arg[j + 1] != NULL)
		pos = ft_atoi(arg[j + 1]);
	if (pos <= 0 || pos > (*h)->histsize)
	{
		history_out(arg[j], i);
		return (1);
	}
	history_del_pos(pos);
	return (0);
}

int				history_del_pos(int pos)
{
	t_hist		*h;

	h = NULL;
	h = ft_close_hist(GET_HIST, NULL);
	if (h == NULL)
	{
		history_out(NULL, pos);
		return (1);
	}
	while (h)
	{
		if (h->id == pos)
		{
			// a faire
			printf("delete maillon %d\n", pos);
		}
		h = h->next;
	}
	return (0);
}
*/
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

int			ft_print_history_len(int nb)
{
	t_hist	*h;
	int		i;
	int		histsize;

	h = NULL;
	i = 0;
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
**	HISTSIZE a aller recuperer dans les variables set
*/

int				ft_history(char **arg, char ***env)
{
	t_opt_h		*hist_opt;

	(void)env;
	if (arg == NULL)
		return (1);
	if (ft_len_tab(arg) == 1)
		return (ft_print_history());
	hist_opt = check_hist(arg);
	if (hist_opt == NULL)
		return (1);
	printf("*** DEBUG ***\n");
	printf("h->c = %d\n", hist_opt->c);
	printf("h->d = %d\n", hist_opt->d);
	printf("h->a = %d\n", hist_opt->a);
	printf("h->n = %d\n", hist_opt->n);
	printf("h->r = %d\n", hist_opt->r);
	printf("h->w = %d\n", hist_opt->w);
	printf("h->p = %d\n", hist_opt->p);
	printf("h->s = %d\n", hist_opt->s);
	printf("h->offset = %d\n", hist_opt->c);
	printf("h->filename = %s\n", hist_opt->filename);
	printf("*** END ***\n");
	histo_suite(hist_opt);
	hist_opt = delete_struct_hist(hist_opt);
	return (0);
}
