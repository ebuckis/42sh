/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_s.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 16:26:36 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 10:03:33 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_s_flag(t_field *cur)
{
	if ((cur->flag & MINUS) && (cur->flag & ZERO))
		cur->flag -= ZERO;
	if ((cur->flag & PLUS) && (cur->flag & SPACE))
		cur->flag -= SPACE;
}

static void			ft_printf_s_space(t_field *cur)
{
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
}

void				ft_printf_s(t_field *cur, va_list *va)
{
	char		*str;

	str = va_arg(*va, char*);
	cur->l = (str == 0) ? 6 : ft_strlen(str);
	ft_printf_s_flag(cur);
	if (cur->preci >= 0 && cur->l > cur->preci)
		cur->l = cur->preci;
	ft_printf_s_space(cur);
	cur->ret += (str) ? ft_putstr_sizel(str, cur->l) : ft_putstr_sizel("(null)",
		cur->l);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}

void				ft_printf_ss(t_field *cur, va_list *va)
{
	wchar_t		*wstr;

	wstr = va_arg(*va, int*);
	cur->l = (wstr == 0) ? 6 : ft_wstrlen(wstr);
	cur->l = (MB_CUR_MAX == 1 && wstr) ? ft_wstrlen_single(wstr) : cur->l;
	ft_printf_s_flag(cur);
	if (cur->preci >= 0 && cur->l > cur->preci)
	{
		cur->l = (wstr == 0) ? cur->preci : ft_wstrlenl(wstr, cur->preci);
		cur->l = (MB_CUR_MAX == 1 && wstr) ? cur->preci : cur->l;
	}
	ft_printf_s_space(cur);
	if (MB_CUR_MAX == 1 && wstr)
		cur->ret += ft_putwstr_singlel(wstr, cur->l);
	else
		cur->ret += (wstr) ? ft_putwstrl(wstr, cur->l) :
			ft_putstr_sizel("(null)", cur->l);
	cur->ret += ft_putchar_sizel(' ', cur->spc_aft);
}
