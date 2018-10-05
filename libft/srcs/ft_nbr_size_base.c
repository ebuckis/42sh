/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbr_size_base.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/06 14:31:38 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 15:09:21 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbr_size_base(unsigned int n, unsigned int base)
{
	int		ret;

	ret = 0;
	if (n >= base)
	{
		ret += ft_nbr_size_base(n / base, base);
		ret += ft_nbr_size_base(n % base, base);
	}
	else
		ret += 1;
	return (ret);
}

int		ft_nbr_long_size_base(unsigned long int n, unsigned long int base)
{
	int		ret;

	ret = 0;
	if (n >= base)
	{
		ret += ft_nbr_long_size_base(n / base, base);
		ret += ft_nbr_long_size_base(n % base, base);
	}
	else
		ret += 1;
	return (ret);
}
