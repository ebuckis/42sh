/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_x2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 11:50:22 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/12 11:51:56 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_lx(t_field *cur, va_list *va)
{
	unsigned long	lx;

	lx = va_arg(*va, unsigned long);
	cur->l = (cur->preci == 0 && lx == 0) ? 0 : ft_nbr_long_size_base(lx, 16);
	cur->l += ((cur->flag & SHARP) && lx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && lx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && lx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && lx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && lx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || lx) ? ft_putnbr_long_base(lx, 16, 0) :
			0;
	else
		cur->ret += (cur->preci != 0 || lx) ? ft_putnbr_long_base(lx, 16, 1) :
			0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_llx(t_field *cur, va_list *va)
{
	unsigned long long	llx;

	llx = va_arg(*va, unsigned long long);
	cur->l = (cur->preci == 0 && llx == 0) ? 0 : ft_nbr_long_size_base(llx, 16);
	cur->l += ((cur->flag & SHARP) && llx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && llx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && llx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && llx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && llx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || llx) ? ft_putnbr_long_base(llx, 16, 0)
			: 0;
	else
		cur->ret += (cur->preci != 0 || llx) ? ft_putnbr_long_base(llx, 16, 1)
			: 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_jx(t_field *cur, va_list *va)
{
	uintmax_t	jx;

	jx = va_arg(*va, uintmax_t);
	cur->l = (cur->preci == 0 && jx == 0) ? 0 : ft_nbr_long_size_base(jx, 16);
	cur->l += ((cur->flag & SHARP) && jx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && jx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && jx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && jx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && jx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || jx) ? ft_putnbr_long_base(jx, 16, 0)
			: 0;
	else
		cur->ret += (cur->preci != 0 || jx) ? ft_putnbr_long_base(jx, 16, 1)
			: 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_zx(t_field *cur, va_list *va)
{
	size_t	zx;

	zx = va_arg(*va, size_t);
	cur->l = (cur->preci == 0 && zx == 0) ? 0 : ft_nbr_long_size_base(zx, 16);
	cur->l += ((cur->flag & SHARP) && zx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && zx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && zx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && zx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && zx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || zx) ? ft_putnbr_long_base(zx, 16, 0)
			: 0;
	else
		cur->ret += (cur->preci != 0 || zx) ? ft_putnbr_long_base(zx, 16, 1)
			: 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
