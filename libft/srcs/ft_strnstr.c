/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 08:27:05 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:15:34 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t i;
	size_t j;

	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (j < n && haystack[j])
	{
		i = 0;
		while (haystack[j + i] == needle[i] && (j + i) < n)
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
