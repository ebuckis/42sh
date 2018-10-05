/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_o1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 10:00:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/12 10:00:51 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_o_flag_space(t_field *cur)
{
	cur->zero = (cur->preci > cur->l) ? cur->preci - cur->l : 0;
	if ((cur->preci >= 0 || (cur->flag & MINUS)) && (cur->flag & ZERO))
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
	cur->ret += (cur->flag & SHARP) ? ft_putchar_size('0') : 0;
}

void		ft_printf_hho(t_field *cur, va_list *va)
{
	unsigned char	hho;

	hho = (unsigned char)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && hho == 0) ? 0 : ft_nbr_size_base(hho, 8);
	cur->l += (cur->flag & SHARP && hho) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || hho) && (cur->preci || hho))
		cur->ret += ft_putnbr_base(hho, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_ho(t_field *cur, va_list *va)
{
	unsigned short	ho;

	ho = (unsigned short)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && ho == 0) ? 0 : ft_nbr_size_base(ho, 8);
	cur->l += (cur->flag & SHARP && ho) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || ho) && (cur->preci || ho))
		cur->ret += ft_putnbr_base(ho, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_o(t_field *cur, va_list *va)
{
	unsigned int	o;

	o = va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && o == 0) ? 0 : ft_nbr_size_base(o, 8);
	cur->l += (cur->flag & SHARP && o) ? 1 : 0;
	ft_printf_o_flag_space(cur);
	if ((!(cur->flag & SHARP) || o) && (cur->preci || o))
		cur->ret += ft_putnbr_base(o, 8, 0);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
