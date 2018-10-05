/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 10:51:59 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 10:54:44 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *str, int n)
{
	char	*cpy;

	cpy = ft_strnew(n);
	if (!cpy)
		return (NULL);
	cpy = ft_strcpy(cpy, str);
	free(str);
	str = cpy;
	return (str);
}
