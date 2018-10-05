/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_maj_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 19:02:42 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:02:43 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_maj_line(t_navig *n)
{
	char	*ret;

	ret = NULL;
	if (!(ret = tgetstr("sc", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	if (!(ret = tgetstr("vi", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	if (!(ret = tgetstr("cd", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	ft_putstr(n->s + n->i);
	if (!(ret = tgetstr("ve", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	if (!(ret = tgetstr("rc", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	return (1);
}

/*
** save cursor
** cursor invisible
** del jusqu'a la fin
** impression de la new str
** cursor visible
** restor cursor
** x_len += i;
** y_len += i;
*/
