/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 14:27:00 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/05 14:28:03 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static t_field		*ft_init(t_field *cur)
{
	cur->flag = 0;
	cur->width = 0;
	cur->width_ast = 0;
	cur->preci = -1;
	cur->preci_ast = 0;
	cur->conv = 0;
	cur->type = 0;
	cur->letter = 0;
	cur->len = 0;
	cur->nb = 0;
	cur->ret = 0;
	cur->l = 0;
	cur->spc_bfr = 0;
	cur->spc_aft = 0;
	cur->zero = 0;
	cur->plus = 0;
	cur->minus = 0;
	cur->pos = 0;
	cur->error = 0;
	cur->next = NULL;
	return (cur);
}

static t_field		*ft_add(t_field *cur, int i)
{
	if (cur == NULL)
	{
		if ((cur = (t_field*)malloc(sizeof(t_field))) == NULL)
			return (NULL);
	}
	else
	{
		if ((cur->next = (t_field*)malloc(sizeof(t_field))) == NULL)
			return (NULL);
		cur = cur->next;
	}
	cur->text = i - 1;
	cur = ft_init(cur);
	return (cur);
}

void				ft_parse3(const char *str, int i, t_field *cur)
{
	if (str[i] == '+' || str[i] == '#')
	{
		cur->flag += ((str[i] == '+') && !(cur->flag & PLUS)) ? PLUS : 0;
		cur->flag += ((str[i] == '#') && !(cur->flag & SHARP)) ? SHARP : 0;
	}
	else if (!ft_strchr(FLAG, str[i]) && !ft_strchr(WIDTH, str[i]) && str[i]
			!= '.' && !ft_strchr(CONV, str[i]) && !ft_strchr(TYPE, str[i]))
	{
		cur->letter = str[i];
		cur->nb = 5;
	}
}

static t_field		*ft_parse2(const char *str, int i, t_field *cur,
		va_list *va)
{
	while (str[++i] && cur->nb != 5)
	{
		if (ft_strchr(FLAG, str[i]) != NULL && cur->nb < 2)
			cur = ft_flags(cur, str, i);
		else if (ft_strchr(WIDTH, str[i]) != NULL && cur->nb < 2)
			cur = ft_width(cur, str, i, va);
		else if (str[i] == '.' && cur->nb < 3)
			cur = ft_preci(cur, str, i, va);
		else if (ft_strchr(CONV, str[i]) != NULL && cur->nb < 5 && cur->conv
				< J_FLAG)
			cur = ft_sizem(cur, str, i);
		else if (ft_strchr(TYPE, str[i]) != NULL)
			cur = ft_type(cur, str, i, va);
		else
			ft_parse3(str, i, cur);
		cur->len++;
	}
	return (cur);
}

t_field				*ft_parse(const char *str, va_list *va)
{
	t_field		*cur;
	t_field		*begin;
	int			i;

	i = -1;
	begin = NULL;
	cur = NULL;
	while (str[++i] && (cur == NULL || cur->error == 0))
	{
		if (str[i] == '%')
		{
			if (begin == NULL)
			{
				if ((begin = ft_add(begin, i)) == NULL)
					return (NULL);
				cur = begin;
			}
			else if ((cur = ft_add(cur, i)) == NULL)
				return (NULL);
			cur = ft_parse2(str, i, cur, va);
			i += cur->len;
		}
	}
	return (begin);
}
