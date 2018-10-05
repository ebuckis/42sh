/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_u1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 16:50:57 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 17:30:59 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_u_flag_space(t_field *cur)
{
	if ((cur->preci >= 0 || (cur->flag & MINUS)) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
	if (cur->preci > cur->l)
		cur->zero = cur->preci - cur->l;
	if (cur->width > cur->l && (cur->flag & ZERO))
		cur->zero = (cur->width - cur->l > cur->zero) ? cur->width - cur->l :
			cur->zero;
	if (cur->width > cur->l + cur->zero && !(cur->flag & ZERO) &&
		!(cur->flag & MINUS))
		cur->spc_bfr = cur->width - cur->l - cur->zero;
	if (cur->width > cur->l + cur->zero && (cur->flag & MINUS))
		cur->spc_aft = cur->width - cur->l - cur->zero;
	cur->ret += ft_putchar_sizel(' ', cur->spc_bfr);
	cur->ret += ft_putchar_sizel('0', cur->zero);
}

void		ft_printf_hhu(t_field *cur, va_list *va)
{
	unsigned char	hhu;

	hhu = (unsigned char)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && hhu == 0) ? 0 : ft_nbr_u_size(hhu);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || hhu != 0)
		cur->ret += ft_putnbr_u_size(hhu);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_hu(t_field *cur, va_list *va)
{
	unsigned short	hu;

	hu = (unsigned short)va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && hu == 0) ? 0 : ft_nbr_u_size(hu);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || hu != 0)
		cur->ret += ft_putnbr_u_size(hu);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_u(t_field *cur, va_list *va)
{
	unsigned int	u;

	u = va_arg(*va, unsigned int);
	cur->l = (cur->preci == 0 && u == 0) ? 0 : ft_nbr_u_size(u);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || u != 0)
		cur->ret += ft_putnbr_u_size(u);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_lu(t_field *cur, va_list *va)
{
	unsigned long int	lu;

	lu = va_arg(*va, unsigned long int);
	cur->l = (cur->preci == 0 && lu == 0) ? 0 : ft_nbr_u_long_size(lu);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || lu != 0)
		cur->ret += ft_putnbr_u_long_size(lu);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
