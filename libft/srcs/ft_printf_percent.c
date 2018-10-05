/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_percent.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:12:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 12:26:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_percent(t_field *cur)
{
	if ((cur->flag & MINUS) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->width > 1 && (cur->flag & ZERO))
		cur->zero = cur->width - 1;
	if (cur->width > 1 + cur->zero && !(cur->flag & ZERO) && !(cur->flag &
		MINUS))
		cur->spc_bfr = cur->width - 1 - cur->zero;
	if (cur->width > 1 + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - 1 - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putchar_sizel('0', cur->zero);
	cur->ret += ft_putchar_size('%');
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_z(t_field *cur)
{
	cur->l = 1;
	if ((cur->flag & MINUS) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->width > cur->l && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
		cur->zero;
	if (cur->width > cur->l + cur->zero && !(cur->flag & ZERO) && !(cur->flag &
		MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putchar_sizel('0', cur->zero);
	cur->ret += ft_putchar_size(cur->letter);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
