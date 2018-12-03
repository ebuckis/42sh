/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_func.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 17:49:20 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 15:08:13 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/autocomp.h"

/*
** Sends to up, down, right and left arrow functions.
*/

static void	arrow_cmds(t_navig *info, t_slct *slct, char *buf)
{
	if (KEY_CODE_RIGHT)
		ac_right_key(info, slct);
	else if (KEY_CODE_LEFT)
		ac_left_key(info, slct);
	else if (KEY_CODE_UP)
		ac_up_key(info, slct);
	else if (KEY_CODE_DOWN)
		ac_down_key(info, slct);
	else if (KEY_CODE_TAB)
		ac_tab_key(info, slct);
}

/*
** Gets the key that is typed.
*/

int			key_input(t_navig *info, t_slct *slct, int *loop)
{
	char	buf[50];

	ft_bzero(buf, 50);
	read(0, buf, 49);
	if (buf[3] || buf[0] > 127)
		return (0);
	if ((KEY_CODE_RIGHT) || (KEY_CODE_LEFT) || (KEY_CODE_UP)
	|| (KEY_CODE_DOWN) || (KEY_CODE_TAB))
		arrow_cmds(info, slct, buf);
	else if ((buf[0] == 10 && buf[1] == 0) || (KEY_CODE_DEL)
	|| ft_isprint(*buf))
	{
		restore_curs(info, slct);
		if (ft_isprint(*buf))
			ft_new_char(info, buf);
		return ((*loop = 0));
	}
	else
		reset_screen(info);
	return (1);
}

/*
** Erases the display of the list so that only the command line remains.
*/

void		erase_prev(t_navig *info)
{
	reset_screen(info);
	tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	ft_put_prompt(info->col, info->prompt);
	if (info->s)
		ft_putstr(info->s);
}

static void	restore2(t_navig *info, t_slct *tmp)
{
	int	i;

	i = 0;
	if (info->letters && last_char(info->s) != ' ')
		while (info->letters[i])
			i++;
	while (tmp->name[i])
	{
		ft_new_char(info, &tmp->name[i]);
		ft_move_to_xy(info->x, info->y);
		i++;
	}
}

/*
** Puts back th cursor in the command line after displaying
** the list.
*/

void		restore_curs(t_navig *info, t_slct *slct)
{
	t_slct	*tmp;

	tmp = ac_first_elem(slct);
	reset_screen(info);
	if (slct->next->next != slct)
		tputs(tgetstr("up", NULL), 1, ft_putchar_err);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_err);
	ft_put_prompt(info->col, info->prompt);
	if (info->s)
		ft_putstr(info->s);
	ft_recup_pos(&info->x, &info->y);
	while (!tmp->current)
		tmp = tmp->next;
	if (tmp->name)
		restore2(info, tmp);
	if (tmp->is_dir)
	{
		ft_new_char(info, "/");
		ft_move_to_xy(info->x, info->y);
	}
	ft_recup_pos(&info->x, &info->y);
}
