/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sum.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/27 14:16:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 18:19:34 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char				*ft_sum_integer(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	int		carry;

	if (!s1 || !s2)
		return ((s1) ? ft_strdup(s1) : ft_strdup(s2));
	len = (ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2);
	len++;
	if ((result = ft_strnew(len)) == NULL)
		return (NULL);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	carry = 0;
	while (--len >= 0)
	{
		result[len] += carry;
		result[len] += (i >= 0) ? s1[i--] - '0' : 0;
		result[len] += (j >= 0) ? s2[j--] - '0' : 0;
		carry = result[len] / 10;
		result[len] = result[len] % 10 + '0';
	}
	result = (result[0] == '0') ? ft_strcpy(result, &result[1]) : result;
	return (result);
}

char				*ft_sum_fraction(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	int		carry;

	if (!s1 || !s2)
		return ((s1) ? ft_strdup(s1) : ft_strdup(s2));
	len = (ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2);
	if ((result = ft_strnew(len)) == NULL)
		return (NULL);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	carry = 0;
	while (--len >= 2)
	{
		result[len] += carry;
		result[len] += (i >= j) ? s1[i--] - '0' : 0;
		result[len] += (j > i) ? s2[j--] - '0' : 0;
		carry = result[len] / 10;
		result[len] = result[len] % 10 + '0';
	}
	result[1] = '.';
	result[0] = carry + '0';
	return (result);
}

char				*ft_sum_mixt(char *s1_int, char *s1_frac, char *s2_int,
		char *s2_frac)
{
	char	*res;
	char	*res_frac;
	char	*res_int;

	res_int = ft_sum_integer(s1_int, s2_int);
	res_frac = ft_sum_fraction(s1_frac, s2_frac);
	res_int[0] += (res_frac[0] == '1') ? 1 : 0;
	res_int[0] = (res_int[0] == ':') ? '0' : res_int[0];
	res_frac[0] = '0';
	if ((res = ft_strnew(ft_strlen(res_int) + ft_strlen(res_frac) - 1)) == NULL)
		return (NULL);
	res = ft_strcpy(res, res_int);
	res = ft_strcat(res, &res_frac[1]);
	ft_memdel((void**)&res_int);
	ft_memdel((void**)&res_frac);
	return (res);
}

static void			ft_clean(char *s1, char *s2, char *s3, char *s4)
{
	ft_memdel((void**)&s1);
	ft_memdel((void**)&s2);
	ft_memdel((void**)&s3);
	ft_memdel((void**)&s4);
}

char				*ft_sum(char *s1, char *s2, int end)
{
	char	*result;
	char	*s1_int;
	char	*s1_frac;
	char	*s2_int;
	char	*s2_frac;

	if (!s1 || !s2)
		return ((s1) ? ft_strdup(s1) : ft_strdup(s2));
	if (ft_inf_one(s1) >= 0 && ft_inf_one(s2) >= 0)
		result = ft_sum_fraction(s1, s2);
	else if (ft_dot(s1) >= 0 || ft_dot(s2) >= 0)
	{
		s1_int = ft_integer(s1);
		s1_frac = ft_fraction(s1);
		s2_int = ft_integer(s2);
		s2_frac = ft_fraction(s2);
		result = ft_sum_mixt(s1_int, s1_frac, s2_int, s2_frac);
		if (end && result[ft_strlen(result) - 1] == '0')
			result[ft_strlen(result) - 1] = 0;
		ft_clean(s1_int, s1_frac, s2_int, s2_frac);
	}
	else
		result = ft_sum_integer(s1, s2);
	return (result);
}
