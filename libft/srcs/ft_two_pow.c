/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_two_pow.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/27 12:27:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/28 17:10:49 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_two_times2(char *factor, char *product, int i, int *carry)
{
	while (--i >= 0)
	{
		if (factor[i] < '5')
		{
			product[i] = ((factor[i] - '0') * 2) + '0' + *carry;
			*carry = 0;
		}
		else
		{
			product[i] = ((factor[i] - '0') * 2) % 10 + '0' + *carry;
			*carry = 1;
		}
	}
	return (product);
}

static char		*ft_two_times3(char *factor, char *product, int i, int *carry)
{
	while (--i >= 0)
	{
		if (!i)
			product[0] = *carry + '0';
		else if (factor[i - 1] < '5')
		{
			product[i] = ((factor[i - 1] - '0') * 2) + '0' + *carry;
			*carry = 0;
		}
		else
		{
			product[i] = ((factor[i - 1] - '0') * 2) % 10 + '0' + *carry;
			*carry = 1;
		}
	}
	return (product);
}

static char		*ft_two_times(char *factor)
{
	int		len_factor;
	int		len_product;
	char	*product;
	int		i;
	int		carry;

	carry = 0;
	len_factor = ft_strlen(factor);
	len_product = (factor[0] >= '5') ? len_factor + 1 : len_factor;
	if ((product = ft_strnew(len_product)) == NULL)
		return (NULL);
	i = len_product;
	if (factor[0] < '5')
		product = ft_two_times2(factor, product, i, &carry);
	else
		product = ft_two_times3(factor, product, i, &carry);
	return (product);
}

static char		*ft_two_pow_plus(int pow)
{
	char	*result;
	char	*buff;
	int		i;

	if ((result = ft_strnew(1)) == NULL)
		return (NULL);
	result[0] = '1';
	i = pow;
	if (pow == 0)
		return (result);
	else
	{
		while (--i >= 0)
		{
			buff = ft_strdup(result);
			ft_memdel((void**)&result);
			if ((result = ft_two_times(buff)) == NULL)
				return (result);
			ft_memdel((void**)&buff);
		}
	}
	return (result);
}

char			*ft_two_pow(int pow)
{
	char	*result;

	if (pow < 0)
		result = ft_two_pow_minus(pow);
	else
		result = ft_two_pow_plus(pow);
	return (result);
}
