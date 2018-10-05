/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup_wchar.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 16:33:52 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 16:34:40 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_strdup_wchar(char *str)
{
	wchar_t	*wstr;
	int		i;

	i = 0;
	wstr = (wchar_t *)malloc(sizeof(*wstr) * (ft_strlen(str) + 1));
	if (wstr == NULL)
		return (NULL);
	while (str[i])
	{
		wstr[i] = (str[i] == -1) ? L'·' : str[i];
		i++;
	}
	wstr[i] = '\0';
	return (wstr);
}
