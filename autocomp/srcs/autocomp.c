/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 13:07:19 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 15:59:32 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"
#include "../../edition/includes/ft_edition.h"

static void	end_key(t_navig *n)
{
	n->x = n->x_len;
	n->y = n->y_len;
	n->i = ft_strlen(n->s);
}

/*
** Checks if the terminal window is big enough
** to display the list.
*/

static int	win_big_enough(t_navig *info)
{
	int		rows;
	int		line;

	line = (ft_strlen(info->prompt) + ft_strlen(info->s)) / info->x_size;
	line += (ft_strlen(info->prompt) + ft_strlen(info->s)) % info->x_size ?
		1 : 0;
	rows = get_row_number(info);
	if (info->y_size - line - rows > 0)
		return (1);
	else
		return (0);
}

/*
** Infinite loop while navigating in the autocomp linked list.
*/

static void	infinite_loop(t_navig *info, t_slct *slct)
{
	int	loop;

	loop = 1;
	while (loop)
	{
		ft_move_to_xy(info->ac_x, info->ac_y);
		if (info->out)
		{
			free_slct(slct, info);
			return ;
		}
		if (loop && win_big_enough(info) &&
		key_input(info, slct, &loop))
			display(info, slct);
		else if (!win_big_enough(info))
		{
			tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
			free_slct(slct, info);
			return ;
		}
	}
	free_slct(slct, info);
	ft_recup_pos(&info->x, &info->y);
	info->x_len = info->x;
	info->y_len = info->y;
	end_key(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_err);
}

/*
** Checks exceptions and quits if there is an
** exception case.
*/

static int	ac_special_cases(t_slct *slct, t_navig *info)
{
	if (!slct || !win_big_enough(info))
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_err);
		free_slct(slct, info);
		return (1);
	}
	if (slct->next->next == slct)
	{
		slct->current = 0;
		slct->next->current = 1;
		ft_move_to_xy(0, info->ac_y);
		restore_curs(info, slct);
		free_slct(slct, info);
		return (1);
	}
	return (0);
}

/*
** Inits the autocomp linked list and starts
** an infinite loop.
*/

void		autocomp(t_navig *info)
{
	t_slct	*slct;
	char	*line;

	line = NULL;
	info->out = 0;
	info->ac_x = info->x;
	info->ac_y = info->y;
	if (info->s && ft_strcmp(info->s, ""))
		line = ft_strdup(info->s);
	line = get_last_word(line, info);
	g_slct = init_slct(&line, info);
	slct = g_slct;
	if (line != NULL)
		ft_strdel(&line);
	ac_get_info(slct, info);
	if (ac_special_cases(slct, info))
		return ;
	update_index(slct);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_err);
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	end_key(info);
	ft_move_to_xy(0, info->ac_y + 1);
	ft_recup_pos(&info->ac_x, &info->ac_y);
	display(info, slct);
	infinite_loop(info, slct);
}
