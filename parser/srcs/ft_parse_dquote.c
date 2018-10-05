/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_dquote.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:21:39 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 19:26:24 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

int			ft_parse_dquote(t_parse *p)
{
	p->i++;
	while (1)
	{
		if (p->s[p->i] == '\\')
		{
			if (p->s[p->i + 1] == '`' || p->s[p->i + 1] == '$'
				|| p->s[p->i + 1] == '\\' || p->s[p->i + 1] == '\"')
				p->i++;
			ft_end_while(p, DOUBLE_QUOTE);
		}
		else if (p->s[p->i] == '\"')
		{
			p->i++;
			return (1);
		}
		else if (p->s[p->i] != '\0')
			ft_end_while(p, DOUBLE_QUOTE);
		else
		{
			if (!(ft_suite_line(p, 1, "dquote> ")))
				return (0);
		}
	}
	return (1);
}

/*
** Gestion des "..."
** s'il est seul on boucle dans ft_suite
** gestion particuliere si on a un backslash
**
** on ressort dès qu'on a un autre "
*/
