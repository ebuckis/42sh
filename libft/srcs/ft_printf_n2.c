/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_n2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 16:44:43 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 16:50:10 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_jn(va_list *va, int *ret)
{
	intmax_t	*p_intmax_t;

	p_intmax_t = va_arg(*va, intmax_t*);
	*p_intmax_t = (intmax_t)*ret;
}

void		ft_printf_zn(va_list *va, int *ret)
{
	ssize_t			*p_ssize_t;

	p_ssize_t = va_arg(*va, ssize_t*);
	*p_ssize_t = (ssize_t)*ret;
}
