/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_c.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:15:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/16 18:47:47 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_c(t_field *cur, va_list *va)
{
	char		c;

	c = (char)va_arg(*va, int);
	cur->l = 1;
	if ((cur->flag & MINUS) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->width > cur->l && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
		cur->zero;
	if (cur->width > cur->l + cur->zero && !(cur->flag & ZERO) && !(cur->flag
		& MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putchar_sizel('0', cur->zero);
	cur->ret += ft_putchar_size(c);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_cc(t_field *cur, va_list *va)
{
	wchar_t		wc;

	wc = (wchar_t)va_arg(*va, int);
	cur->l = (MB_CUR_MAX == 1) ? 1 : ft_wcharlen(wc);
	if ((cur->flag & MINUS) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->width > cur->l && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l
		: cur->zero;
	if (cur->width > cur->l + cur->zero && !(cur->flag & ZERO) && !(cur->flag &
		MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (MB_CUR_MAX == 1)
		cur->ret += ft_putchar_size(wc);
	else
		cur->ret += ft_putwchar(wc);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
