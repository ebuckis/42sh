/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_x1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 11:49:52 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/12 11:52:21 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_x_flag(t_field *cur)
{
	if ((cur->preci >= 0 || (cur->flag & MINUS)) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
}

void		ft_printf_x_zero(t_field *cur)
{
	if (cur->width > cur->l && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
			cur->zero;
	if (cur->width > cur->l + cur->zero && !(cur->flag & ZERO) &&
		!(cur->flag & MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
}

void		ft_printf_hhx(t_field *cur, va_list *va)
{
	unsigned char	hhx;

	hhx = (unsigned char)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && hhx == 0) ? 0 : ft_nbr_size_base(hhx, 16);
	cur->l += ((cur->flag & SHARP) && hhx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && hhx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && hhx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && hhx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && hhx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || hhx) ? ft_putnbr_base(hhx, 16, 0) : 0;
	else
		cur->ret += (cur->preci != 0 || hhx) ? ft_putnbr_base(hhx, 16, 1) : 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_hx(t_field *cur, va_list *va)
{
	unsigned short		hx;

	hx = (unsigned short)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && hx == 0) ? 0 : ft_nbr_size_base(hx, 16);
	cur->l += ((cur->flag & SHARP) && hx) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && hx)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && hx))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && hx) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && hx) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || hx) ? ft_putnbr_base(hx, 16, 0) : 0;
	else
		cur->ret += (cur->preci != 0 || hx) ? ft_putnbr_base(hx, 16, 1) : 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_x(t_field *cur, va_list *va)
{
	unsigned int	x;

	x = va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && x == 0) ? 0 : ft_nbr_size_base(x, 16);
	cur->l += ((cur->flag & SHARP) && x) ? 2 : 0;
	ft_printf_x_flag(cur);
	if (cur->preci > cur->l - 2 && (cur->flag & SHARP) && x)
		cur->zero = cur->preci - cur->l + 2;
	if (cur->preci > cur->l && !((cur->flag & SHARP) && x))
		cur->zero = cur->preci - cur->l;
	ft_printf_x_zero(cur);
	if (cur->type & X_MIN)
		cur->ret += (cur->flag & SHARP && x) ? ft_putstr_size("0x") : 0;
	else
		cur->ret += (cur->flag & SHARP && x) ? ft_putstr_size("0X") : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->type & X_MIN)
		cur->ret += (cur->preci != 0 || x) ? ft_putnbr_base(x, 16, 0) : 0;
	else
		cur->ret += (cur->preci != 0 || x) ? ft_putnbr_base(x, 16, 1) : 0;
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
