/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 10:10:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/28 17:22:24 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static t_field	*ft_flags2(t_field *cur, const char *str, int i)
{
	if (str[i] == '\'' && !(cur->flag & APOSTROPHE))
		cur->flag += APOSTROPHE;
	if (str[i] == 'b' && !(cur->flag & B_FLAG))
		cur->flag += B_FLAG;
	if (str[i] == 'r' && !(cur->flag & R_FLAG))
		cur->flag += R_FLAG;
	if (str[i] == 'k' && !(cur->flag & K_FLAG))
		cur->flag += K_FLAG;
	return (cur);
}

t_field			*ft_flags(t_field *cur, const char *str, int i)
{
	if (str[i] == '#' && !(cur->flag & SHARP))
		cur->flag += SHARP;
	if (str[i] == '0' && !(cur->flag & ZERO))
		cur->flag += ZERO;
	if (str[i] == '-' && !(cur->flag & MINUS))
		cur->flag += MINUS;
	if (str[i] == '+' && !(cur->flag & PLUS))
		cur->flag += PLUS;
	if (str[i] == ' ' && !(cur->flag & SPACE))
		cur->flag += SPACE;
	if (str[i] == '*' && !(cur->flag & ASTERIX))
		cur->flag += ASTERIX;
	if (str[i] == '$' && !(cur->flag & DOLLAR))
		cur->flag += DOLLAR;
	cur = ft_flags2(cur, str, i);
	cur->nb = 1;
	return (cur);
}

t_field			*ft_width(t_field *cur, const char *str, int i, va_list *va)
{
	int		end_nb;

	end_nb = i;
	while (ft_strchr(" 0123456789+-/t/n/v/f/r", (char)str[end_nb]))
		end_nb++;
	if (str[i] == '*' || str[end_nb] == '*')
	{
		cur->width = va_arg(*va, int);
		cur->width_ast = 1;
		if (cur->width < 0)
		{
			cur->flag += MINUS;
			cur->width = -cur->width;
		}
		if (ft_strchr(" 0123456789+-/t/n/v/f/r", (char)str[end_nb + 1]))
			cur->width = ft_atoi(&str[end_nb + 1]);
	}
	else
		cur->width = ft_atoi(&str[i]);
	cur->nb = 2;
	return (cur);
}

t_field			*ft_preci(t_field *cur, const char *str, int i, va_list *va)
{
	int		end_nb;

	end_nb = i + 1;
	while (ft_strchr(" 0123456789+-/t/n/v/f/r", (char)str[end_nb]))
		end_nb++;
	if (str[i + 1] == '*' || str[end_nb] == '*')
	{
		cur->preci = va_arg(*va, int);
		cur->preci_ast = 1;
		if (cur->preci < 0)
			cur->preci = -1;
		if (ft_strchr(" 0123456789+-/t/n/v/f/r", (char)str[end_nb + 1]))
			cur->preci = ft_atoi(&str[end_nb + 1]);
	}
	else
		cur->preci = ft_atoi(&str[i + 1]);
	cur->nb = 3;
	return (cur);
}

t_field			*ft_sizem(t_field *cur, const char *str, int i)
{
	if (str[i] == 'h' && str[i + 1] != 'h' && str[i - 1] != 'h')
		cur->conv = H_FLAG;
	if (str[i] == 'h' && str[i + 1] == 'h')
		cur->conv = HH_FLAG;
	if (str[i] == 'l' && str[i + 1] != 'l' && str[i - 1] != 'l')
		cur->conv = L_FLAG;
	if (str[i] == 'l' && str[i + 1] == 'l')
		cur->conv = LL_FLAG;
	if (str[i] == 'j')
		cur->conv = J_FLAG;
	if (str[i] == 'z')
		cur->conv = Z_FLAG;
	if (str[i] == 'L' && !(cur->flag & L_MAJ))
		cur->flag += L_MAJ;
	cur->nb = 4;
	return (cur);
}
