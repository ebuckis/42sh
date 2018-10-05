/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_parse.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 10:18:37 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/21 16:45:57 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static void	ft_mise_a_zero(t_parse *p)
{
	p->i = 0;
	p->j = 0;
	p->ret = 0;
	p->child_pid = 0;
	p->nb_hdoc = 0;
	p->arg = NULL;
	p->arg_id = NULL;
	p->hdoc = NULL;
}

t_parse		*ft_init_parse(char *line)
{
	t_parse	*p;

	p = (t_parse *)malloc(sizeof(t_parse));
	if (!p)
		return (NULL);
	p->str = ft_strnew(ft_strlen(line) + 1);
	if (!p->str)
		return (NULL);
	p->ident = ft_strnew(ft_strlen(line) + 1);
	if (!p->ident)
		return (NULL);
	p->s = ft_strdup(line);
	if (!p->ident)
		return (NULL);
	p->err = 1;
	ft_mise_a_zero(p);
	p->len = ft_strlen(line);
	ft_save_struct(p);
	return (p);
}

/*
** Initialisation de la structure
*/
