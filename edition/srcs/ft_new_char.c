/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_new_char.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 16:34:29 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:32:42 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static char	*ft_addchar(char *s, char c, int i)
{
	int		n;
	int		j;
	char	*str;

	n = ft_strlen(s);
	j = 0;
	if (!(str = ft_strnew(n + 1)))
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = c;
	j++;
	while (j < n + 1)
	{
		str[j] = s[j - 1];
		j++;
	}
	ft_strdel(&s);
	s = str;
	return (s);
}

/*
** ajout d'un char dans la current string
*/

int			ft_new_char(t_navig *n, char *buf)
{
	if (ft_verif_term_size(n) > 0)
	{
		if (!(n->s = ft_addchar(n->s, buf[0], n->i)))
			return (0);
		if (!ft_maj_line(n))
			return (0);
		ft_x_change(n, CHAR_AJOUT);
	}
	else
	{
		if (!ft_ring_the_bell())
			return (0);
	}
	return (1);
}

/*
** ajout d'un new char, verif si la taille du terminal le permet
*/
