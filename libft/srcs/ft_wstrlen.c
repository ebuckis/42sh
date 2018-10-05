/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 10:11:18 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 10:11:56 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_wstrlen(wchar_t *wstr)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i])
		{
			ret += ft_wcharlen(wstr[i]);
			i++;
		}
	}
	return (ret);
}

int				ft_wstrlen_single(wchar_t *wstr)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i])
			i++;
	}
	return (i);
}

int				ft_wstrlenl(wchar_t *wstr, int l)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (wstr)
	{
		while (wstr[i] && ret + ft_wcharlen(wstr[i]) <= l)
		{
			ret += ft_wcharlen(wstr[i]);
			i++;
		}
	}
	return (ret);
}
