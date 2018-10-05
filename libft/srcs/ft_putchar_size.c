/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putchar_size.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/01 19:24:28 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/16 18:50:46 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putchar_size(int c)
{
	return (write(1, &c, 1));
}

int		ft_putchar_sizel(char c, int i)
{
	int		ret;

	ret = 0;
	while (i > 0)
	{
		ret += write(1, &c, 1);
		i--;
	}
	return (ret);
}
