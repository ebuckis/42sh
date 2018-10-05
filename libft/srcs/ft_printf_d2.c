/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_d2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 16:47:41 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 11:45:06 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_ld(t_field *cur, va_list *va)
{
	long int	ld;

	ld = va_arg(*va, long int);
	cur->l = (cur->preci == 0 && ld == 0) ? 0 : ft_nbr_long_size(ld);
	ft_printf_d_flag(cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && ld >= 0)
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
	cur->minus = (ld < 0) ? 1 : 0;
	cur->pos_long = (ld < 0 && ld != LONG_MIN) ? -ld : ld;
	if (cur->preci > ft_nbr_long_size(ld) - cur->minus)
		cur->zero = cur->preci - ft_nbr_long_size(ld) + cur->minus;
	ft_printf_d_space(cur);
	if (cur->preci != 0 || ld != 0)
		cur->ret += (ld == LONG_MIN) ? ft_putstr_size("9223372036854775808") :
			ft_putnbr_long_size(cur->pos_long);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void			ft_printf_lld(t_field *cur, va_list *va)
{
	long long int	lld;

	lld = va_arg(*va, long long int);
	cur->l = (cur->preci == 0 && lld == 0) ? 0 : ft_nbr_long_size(lld);
	ft_printf_d_flag(cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && lld >= 0)
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
	cur->minus = (lld < 0) ? 1 : 0;
	cur->pos_long = (lld < 0 && lld != LLONG_MIN) ? -lld : lld;
	if (cur->preci > ft_nbr_long_size(lld) - cur->minus)
		cur->zero = cur->preci - ft_nbr_long_size(lld) + cur->minus;
	ft_printf_d_space(cur);
	if (cur->preci != 0 || lld != 0)
		cur->ret += (lld == LLONG_MIN) ? ft_putstr_size("9223372036854775808") :
			ft_putnbr_long_size(cur->pos_long);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void			ft_printf_jd(t_field *cur, va_list *va)
{
	intmax_t		jd;

	jd = va_arg(*va, intmax_t);
	cur->l = (cur->preci == 0 && jd == 0) ? 0 : ft_nbr_long_size(jd);
	ft_printf_d_flag(cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && jd >= 0)
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
	cur->minus = (jd < 0) ? 1 : 0;
	cur->pos_long = (jd < 0 && jd != INTMAX_MIN) ? -jd : jd;
	if (cur->preci > ft_nbr_long_size(jd) - cur->minus)
		cur->zero = cur->preci - ft_nbr_long_size(jd) + cur->minus;
	ft_printf_d_space(cur);
	if (cur->preci != 0 || jd != 0)
		cur->ret += (jd == INTMAX_MIN) ? ft_putstr_size("9223372036854775808") :
			ft_putnbr_long_size(cur->pos_long);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void			ft_printf_zd(t_field *cur, va_list *va)
{
	ssize_t			zd;

	zd = va_arg(*va, ssize_t);
	cur->l = (cur->preci == 0 && zd == 0) ? 0 : ft_nbr_long_size(zd);
	ft_printf_d_flag(cur);
	if (((cur->flag & PLUS) || (cur->flag & SPACE)) && zd >= 0)
	{
		cur->plus = (cur->flag & PLUS) ? 1 : 2;
		cur->l++;
	}
	cur->minus = (zd < 0) ? 1 : 0;
	if (cur->preci > ft_nbr_long_size(zd) - cur->minus)
		cur->zero = cur->preci - ft_nbr_long_size(zd) + cur->minus;
	ft_printf_d_space(cur);
	cur->pos_long = (zd < 0 && zd != LLONG_MIN) ? -zd : zd;
	if (cur->preci != 0 || zd != 0)
		cur->ret += (zd == LLONG_MIN) ? ft_putstr_size("9223372036854775808") :
			ft_putnbr_long_size(cur->pos_long);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
