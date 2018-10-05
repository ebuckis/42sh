/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_separator.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:15:12 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 11:10:31 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

int			ft_is_red(char c)
{
	if (c == '&')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else
		return (0);
}

int			ft_is_redirection(char c)
{
	if (ft_is_red(c) || c == ';' || c == '|')
		return (1);
	return (0);
}

/*
** On verrifie de maniere booleenne si on est sur un separteur/redirection
** 2 cas :
** 			- le premier char est un chiffre
**			- le premier char est un char de la 1ere fonction
*/

static int	ft_red_right(t_parse *p, int j)
{
	p->tmp_id = REDIR;
	j++;
	if (!p->s[p->i + j])
		return (j);
	if (p->s[p->i + j] == '>')
		return (j + 1);
	else if (p->s[p->i + j] == '&')
	{
		j++;
		if (!p->s[p->i + j])
			return (j);
		else if (p->s[p->i + j] == '-')
			return (j + 1);
		while (ft_isdigit(p->s[p->i + j]))
			j++;
		return (j);
	}
	return (j);
}

static int	ft_is_separator_suite(t_parse *p, int j)
{
	while (ft_isdigit(p->s[p->i + j]))
		j++;
	if (p->s[p->i + j] == '>')
		return (ft_red_right(p, j));
	else if (p->s[p->i + j] == '<')
	{
		if (p->s[p->i + j + 1] && p->s[p->i + j + 1] == '<')
			return (0);
		p->tmp_id = REDIR;
		return (j + 1);
	}
	return (0);
}

int			ft_is_separator(t_parse *p)
{
	int		j;

	j = 0;
	p->tmp_id = 0;
	if (p->s[p->i + j] == '<' && p->s[p->i + 1] && p->s[p->i + 1] == '<')
	{
		p->tmp_id = HEREDOC;
		p->nb_hdoc++;
		return (2);
	}
	else if (p->s[p->i + j] == ';')
	{
		p->tmp_id = SEMICOLON;
		return (j + 1);
	}
	else if (p->s[p->i + j] == '|')
	{
		p->tmp_id = PIPE;
		return (j + 1);
	}
	else if (p->s[p->i + j] == '&')
		return (-1);
	return (ft_is_separator_suite(p, j));
}
