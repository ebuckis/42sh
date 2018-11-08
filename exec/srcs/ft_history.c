/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:41:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 16:48:05 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	delete_hist
*/

int				delete_line_history(t_opt_h **h, char *str, int i)
{
	char	*tmp;
	int		pos;

	tmp = NULL;
	tmp = ft_strsub(str, i, ft_strlen(str) - i);
	pos = ft_atoi(tmp);
	ft_strdel(&tmp);
	if (pos == 0 || pos > (*h)->histsize)
	{
		ft_putstr_fd("42sh: history: ", 2);
		ft_putstr_fd(str + i, 2);
		ft_putstr_fd(": history position out of range", 2);
		return (0);
	}
	// sinon on delete la bonne ligne
	printf("on delete la ligne %d\n", pos);
	return (0);
}

/*
**	Print full historique
*/
/*
static int		ft_print_history(int histsize)
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
*/
/*
** Print end historique (max -> nb)
*/
/*
static int		ft_print_history_len(int nb, int histsize)
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
*/
/*
**	Core History
**	HISTSIZE a aller recuperer dans les variables set
*/

int				ft_history(char **arg, char ***env)
{
	t_opt_h		*hist_opt;

	(void)env;
	hist_opt = check_hist(arg);
	if (hist_opt == NULL)
		return (1);
	hist_opt = delete_struct_hist(hist_opt);
	return (0);
}
