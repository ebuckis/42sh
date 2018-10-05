/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_suite_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 13:54:21 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 08:57:35 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static int	ft_realloc_i(t_parse *p, int i)
{
	p->len += i;
	p->str = ft_realloc(p->str, p->len);
	p->ident = ft_realloc(p->ident, p->len);
	if (!p->str || !p->ident)
		return (0);
	if (!p->str || !p->ident)
		return (0);
	return (1);
}

/*
** permet de reallouer de la memoire sur les 2 char *
** qui fonctionnent ensemble
*/

static int	ft_suite2(int i, t_parse *p)
{
	if (i == 0)
		p->i++;
	else if (i == 1)
	{
		i = 2;
		if (!(p->s = ft_strjoin_del(p->s, "\n")))
			return (-1);
	}
	return (i);
}

int			ft_suite_line(t_parse *p, int i, char *prompt)
{
	char	*tmp;

	if ((i = ft_suite2(i, p)) == -1)
		return (0);
	tmp = ft_edition(prompt);
	if (g_nav.err == SIG_CTRLD)
	{
		ft_strdel(&tmp);
		return (0);
	}
	if (!tmp)
	{
		if (!(ft_realloc_i(p, i)))
			return (0);
		return (1);
	}
	if (!(p->s = ft_strjoin_del(p->s, tmp)))
		return (0);
	if (ft_strlen(tmp) != 0 || i != 0)
	{
		if (!(ft_realloc_i(p, i + ft_strlen(tmp))))
			return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

/*
** Permet de lire de nouveau sur l'entrée standard
** Reallocation de memoire nécessaire
*/

void		ft_end_while(t_parse *p, char c)
{
	p->str[p->j] = p->s[p->i];
	p->ident[p->j] = c;
	p->i++;
	p->j++;
}

/*
** Incrementation standard
*/

void		ft_add_space(t_parse *p)
{
	p->str[p->j] = -1;
	p->ident[p->j] = -1;
	p->j++;
}

/*
** Marque un 'espace' grace au char -1 qui permettra de spliter plus loin
*/
