/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 08:27:54 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 11:15:41 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_word(const char *s, size_t index, char c)
{
	size_t j;

	j = 0;
	while (s[index] != c && s[index] != '\0')
	{
		index++;
		j++;
	}
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	nb_mot;
	size_t	i;
	size_t	j;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	nb_mot = cpt_mot(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_mot + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (nb_mot--)
	{
		while (s[i] == c && i < len)
			i++;
		tab[j++] = ft_strsub(s, i, ft_len_word(s, i, c));
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
