/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_del_char.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 14:45:56 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:54:49 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static char	*ft_supprchar(char *s, int i)
{
	int		n;
	int		j;
	char	*str;

	n = ft_strlen(s);
	j = 0;
	if (!(str = ft_strnew(n)))
		return (NULL);
	while (j < i - 1)
	{
		str[j] = s[j];
		j++;
	}
	while (j < n - 1)
	{
		str[j] = s[j + 1];
		j++;
	}
	str[n - 1] = '\0';
	ft_strdel(&s);
	s = str;
	return (s);
}

/*
** suupression du char dans la string
*/

int			ft_del_char(t_navig *n)
{
	if (n->i != 0)
	{
		if (!(n->s = ft_supprchar(n->s, n->i)))
			return (0);
		ft_x_change(n, CHAR_SUPPR);
		ft_move_to_xy(n->x, n->y);
		ft_maj_line(n);
	}
	return (1);
}

/*
** on regarde si on est pas au debut
** 1 - on del dans s
** 2 - on modifie les positions en x-y
** 3 - on va en x-y calculés
** 4 - on met a jour la ligne affichée
*/
