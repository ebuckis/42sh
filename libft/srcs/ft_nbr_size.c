/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbr_size.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/06 14:27:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 14:46:27 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_nbr_size(int n)
{
	int		ret;

	ret = 0;
	if (n != -2147483648)
	{
		if (n < 0)
		{
			n = -n;
			ret++;
		}
		if (n >= 10)
		{
			ret += ft_nbr_size(n / 10);
			ret += ft_nbr_size(n % 10);
		}
		else
			ret++;
	}
	else
		ret = 11;
	return (ret);
}

int			ft_nbr_long_size(long int n)
{
	int		ret;

	ret = 0;
	if (n != LONG_MIN)
	{
		if (n < 0)
		{
			n = -n;
			ret++;
		}
		if (n >= 10)
		{
			ret += ft_nbr_long_size(n / 10);
			ret += ft_nbr_long_size(n % 10);
		}
		else
			ret++;
	}
	else
		ret = 20;
	return (ret);
}

int			ft_nbr_u_size(unsigned int n)
{
	int		ret;

	ret = 0;
	if (n >= 10)
	{
		ret += ft_nbr_u_size(n / 10);
		ret += ft_nbr_u_size(n % 10);
	}
	else
		ret++;
	return (ret);
}

int			ft_nbr_u_long_size(unsigned long int n)
{
	int		ret;

	ret = 0;
	if (n >= 10)
	{
		ret += ft_nbr_u_long_size(n / 10);
		ret += ft_nbr_u_long_size(n % 10);
	}
	else
		ret++;
	return (ret);
}
