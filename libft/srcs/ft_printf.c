/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 10:37:00 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 16:14:06 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		clean(t_field *field)
{
	t_field		*cur;
	t_field		*next;

	cur = field;
	while (cur)
	{
		next = cur->next;
		ft_memdel((void**)&cur);
		cur = next;
	}
}

static t_field	*ft_printf_arg(t_field *cur, va_list *va, int *i, int *ret)
{
	if (cur->width_ast)
		va_arg(*va, int);
	if (cur->preci_ast)
		va_arg(*va, int);
	*ret += ft_printf_type(cur, va, ret);
	*i += cur->len;
	cur = cur->next;
	return (cur);
}

static int		end(t_field *field, va_list *va, int ret)
{
	clean(field);
	va_end(*va);
	return (ret);
}

static void		ft_printf_txt(t_field *cur, const char *format, int *i,
		int *ret)
{
	*ret += (cur) ? ft_putstr_sizel((char*)&(format[*i]),
		cur->text - *i + 1) : ft_putstr_size((char*)&format[*i]);
	*i = (cur) ? cur->text : ft_strlen(format) - 1;
}

int				ft_printf(const char *format, ...)
{
	t_field		*field;
	t_field		*cur;
	int			i;
	int			ret;
	va_list		va;

	i = -1;
	ret = 0;
	va_start(va, format);
	field = ft_parse(format, &va);
	va_end(va);
	va_start(va, format);
	cur = field;
	while (format[++i])
	{
		if (cur && cur->error == 1)
			return (end(field, &va, -1));
		else if (format[i] == '%')
			cur = ft_printf_arg(cur, &va, &i, &ret);
		else
			ft_printf_txt(cur, format, &i, &ret);
	}
	return (end(field, &va, ret));
}
