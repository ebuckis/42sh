/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub_del.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 14:43:01 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 09:44:27 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub_del(char *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (!s || start > ft_strlen(s))
	{
		ft_strdel(&s);
		return (NULL);
	}
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
	{
		ft_strdel(&s);
		return (NULL);
	}
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	free((void *)s);
	return (str);
}
