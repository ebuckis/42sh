/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_s.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 16:01:31 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 10:48:22 by kcabus      ###    #+. /#+    ###.fr     */
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
	dprintf(2, "///|%s|***\n", string[0]);
	dprintf(2, "///|%s|***\n", string[1]);
	dprintf(2, "///|%s|***\n", string[2]);
	tmp = ft_strjoin(string[0], (char *)string[1]);	
	nb = ft_strlen(tmp) - pos;
	ft_strdel(&(n->s));
	n->s = ft_strjoin(tmp, string[2]);	
	ft_free_tab(&string);
	ft_strdel(&tmp);
	return (nb);
}

/*
** TODO: remplacer la section de string
** retourner la longueur du remplacement
*/