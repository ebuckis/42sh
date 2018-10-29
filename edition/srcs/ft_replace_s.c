/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_s.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 16:01:31 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 14:24:22 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_replace_s(char *s, t_navig *n, int pos)
{
	int		end;
	int		tmp;

	end = pos + 1;
	tmp = 0;
	while (n->s[pos + end] == s[end])
		end++;
	n->s = ft_realloc()
	return (1);
}

/*
** TODO: remplacer la section de string
** retourner la longueur du remplacement
*/