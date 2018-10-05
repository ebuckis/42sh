/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_antislash.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:20:08 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 11:28:39 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

int			ft_antislash(t_parse *p)
{
	if (p->s[p->i + 1] == '\0')
	{
		if (!(ft_suite_line(p, 0, "> ")))
			return (0);
	}
	else
	{
		p->i++;
		ft_end_while(p, BACKSLASH);
	}
	return (1);
}

/*
** Cette fonction gere le \ en fin de chaine de char
*/
