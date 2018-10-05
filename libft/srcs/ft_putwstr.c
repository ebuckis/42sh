/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 08:26:34 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 10:12:19 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_putwstr(wchar_t *wstr)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i])
		{
			ret += ft_putwchar(wstr[i]);
			i++;
		}
	}
	return (ret);
}

int				ft_putwstr_singlel(wchar_t *wstr, int l)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i] && ret + 1 <= l)
		{
			ret += ft_putchar_size(wstr[i]);
			i++;
		}
	}
	return (ret);
}

int				ft_putwstrl(wchar_t *wstr, int l)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i] && ret + ft_wcharlen(wstr[i]) <= l)
		{
			ret += ft_putwchar(wstr[i]);
			i++;
		}
	}
	return (ret);
}
