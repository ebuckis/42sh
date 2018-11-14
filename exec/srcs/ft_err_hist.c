/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_err_hist.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 10:01:38 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 11:46:00 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

int			history_usage(void)
{
	ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or ", 2);
	ft_putstr_fd("history -awrn [filename] or history -ps [arg...]\n", 2);
	return (1);
}

int			history_out_str(char *str)
{
	ft_putstr_fd("42sh: history: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": history position out of range\n", 2);
	return (0);
}

int			history_out(int id)
{
	ft_putstr_fd("42sh: history: ", 2);
	ft_putnbr_fd(id, 2);
	ft_putstr_fd(": history position out of range\n", 2);
	return (0);
}

int			history_invalid(char *str, int i)
{
	ft_putstr_fd("42sh: history: ", 2);
	ft_putstr_fd(str, 2);
	if (i == 1)
		ft_putstr_fd(": invalid option\n", 2);
	else if (i == 2)
		ft_putstr_fd(": numeric argument required\n", 2);
	return (0);
}
