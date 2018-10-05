/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sum2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/27 17:21:53 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/28 11:23:16 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_inf_one(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (i <= (int)ft_strlen(s) && s[i] != '.')
	{
		if (s[i] != '0')
			return (-1);
		i++;
	}
	if (i > (int)ft_strlen(s))
		return (-1);
	else
		return (i);
}

int				ft_dot(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (i <= (int)ft_strlen(s) && s[i] != '.')
	{
		i++;
	}
	if (i > (int)ft_strlen(s))
		return (-1);
	else
		return (i);
}

char			*ft_integer(char *s)
{
	int		i;
	char	*result;
	int		len;

	if (!s)
		return (NULL);
	i = ft_dot(s);
	if (i >= 0)
		len = i;
	else
		len = ft_strlen(s);
	result = ft_strsub(s, 0, len);
	result[len] = 0;
	return (result);
}

char			*ft_fraction(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	if (!s)
		return (NULL);
	i = ft_dot(s);
	len = 2;
	if (i < 0)
		return (NULL);
	if ((result = ft_strnew(len + ft_strlen(s) - i)) == NULL)
		return (NULL);
	result[0] = '0';
	result[1] = '.';
	j = 2;
	while (++i < (int)ft_strlen(s))
		result[j++] = s[i];
	return (result);
}
