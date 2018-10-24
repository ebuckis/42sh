/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 12:53:13 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 14:23:42 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int	ft_strchr_index(const char *s, char c)
{
	int i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_parse_excl(t_navig *n)
{
	int		ident;
	int		pos;

	pos = 0;
	while (ft_strchr_index(n->s, '!') > 0)
	{
		if (ft_is_interpreted(n->s, pos))
		{
			if ((ident = ft_ident_excl(n->s, pos)) < 0)
				return (0);//avec impression du message d'erreur
			ft_replace_line(n, &pos);//modifier la valeur de pos (+= len du remplacement)
		}
	}
	return (1);
}

/*
** a gérer :
** ![char]		->derniere occurence, si pas trouvée "42sh: event not found: %s"
** ![int]		->boucle jusqu'au bon id, sinon "42sh: %s: event not found"
** !-[int]		->va chercher en arriere , error idem
**
** ident prend different val:
** OCCURRENCE
** OCCURRENCE_NULL
** ID_NUM
** ID_NUM_NULL
** LAST_ID_NUM
** LAST_ID_NUM_NULL
*/

