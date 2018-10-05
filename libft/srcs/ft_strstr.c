/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 08:28:04 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:15:43 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0')
	{
		i = 0;
		while (haystack[j + i] == needle[i])
		{
			if (needle[i + 1] == '\0')
				return ((char *)(haystack + j));
			else
				i++;
		}
		j++;
	}
	return (NULL);
}
