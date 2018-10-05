/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_e.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:29:57 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/05 18:55:41 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_e_flag(t_field *cur, t_double *d, int long_double)
{
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	cur->preci = (cur->preci < 0) ? 6 : cur->preci;
	cur->l = (long_double) ? ft_longdoublelen_sci(d, cur) :
		ft_doublelen_sci(d, cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && !(d->s))
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
}

void				ft_printf_e2(t_field *cur, t_double *d)
{
	ft_printf_e_flag(cur, d, 0);
	cur->minus = (d->s && !(d->e == 1024 && d->m)) ? 1 : 0;
	if (cur->preci > cur->l - cur->minus && d->e != 1024)
		cur->zero = cur->preci - cur->l + cur->minus;
	if (cur->width > cur->l && (cur->flag & ZERO) && d->e != 1024)
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
		cur->zero;
	if (cur->width > cur->l + cur->minus + cur->zero && (d->e == 1024 ||
		!(cur->flag & ZERO)) && !(cur->flag & MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->minus - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += (cur->plus == 1) ? ft_putchar_size('+') : 0;
	cur->ret += (cur->plus == 2) ? ft_putchar_size(' ') : 0;
	cur->ret += (cur->minus == 1) ? ft_putchar_size('-') : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	cur->ret += ft_putnbr_double_sci(d, cur);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
	ft_memdel((void**)&d);
}

void				ft_printf_e(t_field *cur, va_list *va)
{
	double		e;
	t_double	*d;

	e = va_arg(*va, double);
	d = ft_double_info(e);
	ft_printf_e2(cur, d);
}

void				ft_printf_le2(t_field *cur, t_double *d)
{
	ft_printf_e_flag(cur, d, 1);
	cur->minus = (d->s && !(d->e == 16385 && d->m)) ? 1 : 0;
	if (cur->preci > cur->l - cur->minus && d->e != 16385)
		cur->zero = cur->preci - cur->l + cur->minus;
	if (cur->width > cur->l && (cur->flag & ZERO) && d->e != 16385)
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
		cur->zero;
	if (cur->width > cur->l + cur->minus + cur->zero && (d->e == 16385 ||
		!(cur->flag & ZERO)) && !(cur->flag & MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->minus - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += (cur->plus == 1) ? ft_putchar_size('+') : 0;
	cur->ret += (cur->plus == 2) ? ft_putchar_size(' ') : 0;
	cur->ret += (cur->minus == 1) ? ft_putchar_size('-') : 0;
	cur->ret += ft_putchar_sizel('0', cur->zero);
	cur->ret += ft_putnbr_longdouble_sci(d, cur);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
	ft_memdel((void**)&d);
}

void				ft_printf_le(t_field *cur, va_list *va)
{
	long double		le;
	t_double		*d;

	le = va_arg(*va, long double);
	d = ft_longdouble_info(le);
	ft_printf_le2(cur, d);
}
