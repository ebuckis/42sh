/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/30 18:56:33 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 15:29:40 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

int			get_row_number(t_navig *info)
{
	int	ret;
	int	cols;

	cols = info->x_size / (info->max_len + 2);
	ret = info->nb_elem / cols;
	ret += info->nb_elem % cols ? 1 : 0;
	return (ret);
}

void		reset_screen(t_navig *info)
{
	int	rows;

	ft_recup_pos(&info->x, &info->y);
	rows = get_row_number(info);
	ft_move_to_xy(0, info->y);
	while (rows > 1)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
		rows--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
}

/*
** Prints the list.
*/

void		display(t_navig *info, t_slct *slct)
{
	int		cols;
	int		rows;
	t_slct	*tmp;

	rows = get_row_number(info);
	cols = info->x_size / (info->max_len + 2);
	tmp = ac_first_elem(slct);
	while (tmp != slct)
	{
		ac_print_arg(tmp, info);
		if (tmp->next != slct && !info->out)
			ft_putstr("  ");
		if (tmp->index % cols == 0 && tmp->next != slct && !info->out)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
			ft_move_to_xy(0, info->y);
		}
		tmp = tmp->next;
	}
}

/*
** Prints directories in red and executable files
** in green.
*/

static void	print_dir_exe(t_slct *slct, t_navig *info)
{
	int	i;

	i = info->max_len - slct->len;
	if (slct->current)
	{
		tputs(tgetstr("so", NULL), 1, ft_putchar_err);
		ft_putstr(L_BLUE);
		ft_printf("%s", slct->name);
		slct->is_dir ? ft_putchar('/') : ft_putchar('*');
		ft_putstr(RESET);
		tputs(tgetstr("se", NULL), 1, ft_putchar_err);
	}
	else
	{
		slct->is_dir ? ft_putstr(RED) : ft_putstr(GREEN);
		ft_printf("%s", slct->name);
		ft_putstr(RESET);
		slct->is_dir ? ft_putchar('/') : ft_putchar('*');
	}
	while (i--)
		ft_putchar(' ');
}

/*
** Prints casual files.
*/

void		ac_print_arg(t_slct *slct, t_navig *info)
{
	int	i;

	if (info->out)
		return ;
	i = info->max_len - slct->len;
	if (slct->is_dir || slct->is_exe)
		print_dir_exe(slct, info);
	else
	{
		if (slct->current)
		{
			tputs(tgetstr("so", NULL), 1, ft_putchar_err);
			ft_putstr(L_BLUE);
			ft_printf("%s", slct->name);
			ft_putstr(RESET);
			tputs(tgetstr("se", NULL), 1, ft_putchar_err);
		}
		else
			ft_printf("%s", slct->name);
		while (i--)
			ft_putchar(' ');
	}
}
