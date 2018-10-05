/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_o2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 10:00:15 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/12 10:01:14 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_lo(t_field *cur, va_list *va)
{
	unsigned long	lo;

	lo = va_arg(*va, unsigned long);
	cur->l = (cur->preci == 0 && lo == 0) ? 0 : ft_nbr_long_size_base(lo, 8);
	cur->l += (cur->flag & SHARP && lo) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || lo) && (cur->preci || lo))
		cur->ret += ft_putnbr_long_base(lo, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_llo(t_field *cur, va_list *va)
{
	unsigned long long	llo;

	llo = va_arg(*va, unsigned long long);
	cur->l = (cur->preci == 0 && llo == 0) ? 0 : ft_nbr_long_size_base(llo, 8);
	cur->l += (cur->flag & SHARP && llo) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || llo) && (cur->preci || llo))
		cur->ret += ft_putnbr_long_base(llo, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_jo(t_field *cur, va_list *va)
{
	uintmax_t	jo;

	jo = va_arg(*va, uintmax_t);
	cur->l = (cur->preci == 0 && jo == 0) ? 0 : ft_nbr_long_size_base(jo, 8);
	cur->l += (cur->flag & SHARP && jo) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || jo) && (cur->preci || jo))
		cur->ret += ft_putnbr_long_base(jo, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_zo(t_field *cur, va_list *va)
{
	size_t	zo;

	zo = va_arg(*va, size_t);
	cur->l = (cur->preci == 0 && zo == 0) ? 0 : ft_nbr_long_size_base(zo, 8);
	cur->l += (cur->flag & SHARP && zo) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || zo) && (cur->preci || zo))
		cur->ret += ft_putnbr_long_base(zo, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
