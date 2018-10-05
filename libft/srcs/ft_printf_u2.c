/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_u2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 16:51:08 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 17:22:36 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_llu(t_field *cur, va_list *va)
{
	unsigned long long int	llu;

	llu = va_arg(*va, unsigned long long int);
	cur->l = (cur->preci == 0 && llu == 0) ? 0 : ft_nbr_u_long_size(llu);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || llu != 0)
		cur->ret += ft_putnbr_u_long_size(llu);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_ju(t_field *cur, va_list *va)
{
	uintmax_t	ju;

	ju = va_arg(*va, uintmax_t);
	cur->l = (cur->preci == 0 && ju == 0) ? 0 : ft_nbr_u_long_size(ju);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || ju != 0)
		cur->ret += ft_putnbr_u_long_size(ju);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void		ft_printf_zu(t_field *cur, va_list *va)
{
	size_t	ju;

	ju = va_arg(*va, size_t);
	cur->l = (cur->preci == 0 && ju == 0) ? 0 : ft_nbr_u_long_size(ju);
	ft_printf_u_flag_space(cur);
	if (cur->preci != 0 || ju != 0)
		cur->ret += ft_putnbr_u_long_size(ju);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
