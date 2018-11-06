/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_s.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 16:01:31 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 13:03:48 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_replace_s(char *s, t_navig *n, int pos)
{
	char	**string;
	char	*tmp;
	int		nb;

	string = (char **)malloc(sizeof(char *) * 4);
	string[0] = ft_strsub(n->s, 0, (size_t)pos);
	string[1] = s;
	string[2] = ft_strdup(n->s + pos + strlen(s));
	string[3] = NULL;
	tmp = ft_strjoin(string[0], (char *)string[1]);	
	nb = ft_strlen(tmp) - pos;
	ft_strdel(&(n->s));
	n->s = ft_strjoin(tmp, string[2]);	
	ft_strdel(&tmp);
	return (nb);
}

/*
** TODO: remplacer la section de string
** retourner la longueur du remplacement
*/