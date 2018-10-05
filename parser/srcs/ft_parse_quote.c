/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_quote.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:22:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 19:21:22 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

int			ft_parse_quote(t_parse *p)
{
	p->i++;
	while (1)
	{
		if (p->s[p->i] == '\'')
		{
			p->i++;
			return (1);
		}
		else if (p->s[p->i] != '\0')
		{
			ft_end_while(p, SINGLE_QUOTE);
		}
		while (p->s[p->i] == '\0')
		{
			if (!ft_suite_line(p, 1, "quote> "))
				return (0);
		}
	}
	return (1);
}

/*
** Gestion des '...'
** On boucle tant qu'on a pas un autre '
** On sort des le 2eme ' rencontré
** 39 '
*/
