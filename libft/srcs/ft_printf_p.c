/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_p.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:33:06 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 12:25:30 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_p(t_field *cur, va_list *va)
{
	unsigned long int	p;

	p = va_arg(*va, unsigned long int);
	cur->l = ft_nbr_long_size_base(p, 16);
	if ((cur->preci >= 0 || (cur->flag & MINUS)) && (cur->flag & ZERO))
		cur->flag -= cur->zero;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->preci > cur->l)
		cur->zero = cur->preci - cur->l;
	if (cur->width > cur->l + 2 && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l - 2 > cur->zero) ? cur->width - cur->l
			- 2 : cur->zero;
	if (cur->width > cur->l + 2 + cur->zero && !(cur->flag & ZERO) &&
		!(cur->flag & MINUS))
		cur->spc_bfr = cur->width - cur->l - 2 - cur->zero;
	if (cur->width > cur->l + 2 + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - 2 - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putstr_size("0x");
	cur->ret += ft_putchar_sizel('0', cur->zero);
	if (cur->preci != 0 || p)
		cur->ret += ft_putnbr_long_base(p, 16, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
