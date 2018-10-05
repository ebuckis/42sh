/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 08:20:27 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:12:59 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*s1;
	char			*s2;

	i = 0;
	s1 = (char *)dst;
	s2 = (char *)src;
	if (src < dst)
		while (len != 0)
		{
			s1[len - 1] = s2[len - 1];
			len--;
		}
	else
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	return (dst);
}
