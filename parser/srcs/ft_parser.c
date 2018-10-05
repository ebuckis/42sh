/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parser.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:16:59 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 17:03:53 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static void	ft_print_parse_err(t_parse *p)
{
	ft_putstr_fd("parse error near : `", 2);
	if (p->s[p->i])
		ft_putchar_fd(p->s[p->i], 2);
	else
		ft_putstr_fd("\\n", 2);
	ft_putstr_fd("'\n", 2);
}

static int	ft_str_parser(t_parse *p)
{
	int		tmp;

	while (p->s[p->i])
	{
		if (p->s[p->i] == '\\')
			p->err = ft_antislash(p);
		else if (p->s[p->i] == '\"')
			p->err = ft_parse_dquote(p);
		else if (p->s[p->i] == '\'')
			p->err = ft_parse_quote(p);
		else if ((tmp = ft_is_separator(p)))
			p->err = ft_separator(p, tmp);
		else if (ft_is_white(p->s[p->i]))
		{
			ft_add_space(p);
			p->i++;
		}
		else
			ft_end_while(p, WORD);
		if (p->err <= 0)
			return (p->err);
	}
	return (1);
}

/*
** dans ft_str_parser on verifie char by char
** si on a :	- un backslash
**				- un "
**				- un '
**				- un separateur
**				- ou un whitespace
**				- sinon on copie betement
*/

t_parse		*ft_parser(char *line, pid_t child_pid, int ret)
{
	t_parse	*p;
	int		n;

	p = NULL;
	if (line)
	{
		if (!(p = ft_init_parse(line)))
			return (NULL);
		if ((n = ft_str_parser(p)) <= 0)
		{
			if (n == -1)
				ft_print_parse_err(p);
			return (NULL);
		}
		p->arg = ft_strsplit(p->str, -1);
		p->arg_id = ft_strsplit(p->ident, -1);
		p->ret = ret;
		p->child_pid = child_pid;
		ft_heredoc(p);
		if (!p->arg && !p->arg_id)
			return (NULL);
	}
	return (p);
}

/*
** Debut de la fonction
** - Initialisation
** - si le parse renvoie une erreur on quitte proprement
** - on split str pour avoir les arg
** - on split ident pour identifier les arguments precedents
*/
