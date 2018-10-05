/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_f.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:30:13 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:15:54 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_f_flag(t_field *cur, t_double *d, int long_double)
{
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	cur->preci = (cur->preci < 0 && !(cur->type & G_MIN) &&
		!(cur->type & G_MAJ)) ? 6 : cur->preci;
	cur->l = (long_double) ? ft_longdoublelen(d, cur) :
		ft_doublelen(d, cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && !(d->s))
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
}

void				ft_printf_f2(t_double *d, t_field *cur)
{
	ft_printf_f_flag(cur, d, 0);
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
	cur->ret += (!(cur->type & G_MIN) && !(cur->type & G_MAJ)) ?
		ft_putchar_sizel('0', cur->zero) : 0;
	cur->ret += ft_putnbr_double(d, cur);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
	ft_memdel((void**)&d);
}

void				ft_printf_f(t_field *cur, va_list *va)
{
	double		f;
	t_double	*d;

	f = va_arg(*va, double);
	d = ft_double_info(f);
	ft_printf_f2(d, cur);
}

void				ft_printf_lf2(t_double *d, t_field *cur)
{
	ft_printf_f_flag(cur, d, 1);
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
	cur->ret += (!(cur->type & G_MIN) && !(cur->type & G_MAJ)) ?
		ft_putchar_sizel('0', cur->zero) : 0;
	cur->ret += ft_putnbr_longdouble(d, cur);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
	ft_memdel((void**)&d);
}

void				ft_printf_lf(t_field *cur, va_list *va)
{
	long double		lf;
	t_double		*d;

	lf = va_arg(*va, long double);
	d = ft_longdouble_info(lf);
	ft_printf_lf2(d, cur);
}
