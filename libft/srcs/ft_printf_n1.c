/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_n1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 16:44:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 16:44:37 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_hhn(va_list *va, int *ret)
{
	signed char	*p_char;

	p_char = va_arg(*va, signed char*);
	*p_char = (signed char)*ret;
}

void		ft_printf_hn(va_list *va, int *ret)
{
	short		*p_short;

	p_short = va_arg(*va, short*);
	*p_short = (short)*ret;
}

void		ft_printf_n(va_list *va, int *ret)
{
	int			*p_int;

	p_int = va_arg(*va, int*);
	*p_int = *ret;
}

void		ft_printf_ln(va_list *va, int *ret)
{
	long		*p_long;

	p_long = va_arg(*va, long*);
	*p_long = (long)*ret;
}

void		ft_printf_lln(va_list *va, int *ret)
{
	long long	*p_ll;

	p_ll = va_arg(*va, long long*);
	*p_ll = (long long)*ret;
}
