/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_whitespace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 09:06:03 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:15:14 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_transforme_s(char *s, char *ret)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t'))
		{
			ret[j] = s[i];
			j++;
		}
		else if (s[i + 1] && (s[i + 1] != ' ' && s[i + 1] != '\t') && j != 0)
		{
			ret[j] = ' ';
			j++;
		}
		i++;
	}
	return (ret);
}

char		*ft_whitespace(char *s)
{
	char	*ret;
	int		n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (n == 0)
		return (NULL);
	if (!(ret = ft_memalloc(n + 1)))
		return (NULL);
	ret = ft_transforme_s(s, ret);
	n = ft_strlen(ret);
	if (n == 0)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
