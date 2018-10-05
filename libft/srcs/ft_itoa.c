/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 08:16:06 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:07:21 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_attrib(long int n1, int i, char *s, int n2)
{
	if (n1 < 0)
	{
		s[0] = '-';
		n1 *= -1;
	}
	while (n2 >= 0)
	{
		s[i] = ((n1 / ft_pw(10, n2)) % 10) + '0';
		n2--;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	int			i;
	int			signe;
	long int	n1;
	long int	n2;
	char		*s;

	n1 = (long int)n;
	i = (n == 0) ? (1) : (0);
	signe = (n < 0) ? (1) : (0);
	n2 = (n < 0) ? (-n) : (n);
	while (n2 != 0)
	{
		n2 /= 10;
		i++;
	}
	s = (char *)malloc(sizeof(char) * i + signe + 1);
	if (!s)
		return (NULL);
	n2 = i - 1;
	i = signe;
	return (ft_attrib(n1, i, s, n2));
}
