/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dollar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:11:36 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/07 13:06:27 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static char		*get_value(char **env, char *key)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(key, "=");
		if (ft_strnequ(env[i], tmp, ft_strlen(tmp)))
		{
			ft_memdel((void**)&tmp);
			return (ft_strdup(env[i] + ft_strlen(key) + 1));
		}
		ft_memdel((void**)&tmp);
	}
	return (NULL);
}

static void		ft_end_dollar(t_parse *p, t_doll *d, int i)
{
	ft_strdel(&(p->arg[i]));
	ft_strdel(&(d->tmp));
	ft_strdel(&(p->arg[i]));
	p->arg[i] = ft_strdup(d->arg);
	ft_strdel(&(d->arg));
	ft_strdel(&(p->arg_id[i]));
	p->arg_id[i] = ft_memalloc(ft_strlen(p->arg[i]) + 1);
	ft_bzero((void*)p->arg_id[i], ft_strlen(p->arg[i]) + 1);
	ft_memset((void*)p->arg_id[i], WORD, ft_strlen(p->arg[i]));
	ft_strdel(&(d->var));
	ft_strdel(&(d->key));
}

static void		ft_getvalue_var(t_parse *p, t_doll *d, int i, int j)
{
	if (p->arg[i][j + 1] == '$')
		d->var = ft_strdup("$");
	else if (p->arg[i][j + 1] == '?')
		d->var = ft_strdup("?");
	else if (d->p1 && d->p2 && d->p2 > d->p1)
		d->var = ft_strsub(d->p1, 1, d->p2 - d->p1 - 1);
	else if (d->p3 && &(p->arg[i][j + 1]) != d->p3)
		d->var = ft_strsub(&(p->arg[i][j + 1]), 0, d->p3 - &(p->arg[i][j + 1]));
	else
		d->var = ft_strdup(&(p->arg[i][j + 1]));
}

static char		*ft_next_dollar_or_space(char *str)
{
	char *p;
	char *next_dollar;
	char *next_sp;
	char *next_nl;

	next_dollar = ft_strchr(str, '$');
	next_sp = ft_strchr(str, ' ');
	next_nl = ft_strchr(str, '\n');
	next_sp = ((next_nl && !next_sp) || (next_nl && next_nl < next_sp))
		? next_nl : next_sp;
	if (next_dollar && next_sp)
		p = (next_dollar < next_sp) ? next_dollar : next_sp;
	else if (next_dollar)
		p = next_dollar;
	else if (next_sp)
		p = next_sp;
	else
		p = NULL;
	return (p);
}

t_parse			*ft_dollar(t_parse *p, int i, int *j, char ***p_env)
{
	t_doll	d;

	d.p1 = ft_strchr(&(p->arg[i][*j + 1]), '{');
	d.p2 = ft_strchr(&(p->arg[i][*j + 1]), '}');
	d.p3 = ft_next_dollar_or_space(&(p->arg[i][*j + 1]));
	ft_getvalue_var(p, &d, i, *j);
	if (ft_strequ(d.var, "$"))
		d.key = ft_itoa(getpid());
	else
		d.key = (ft_strequ(d.var, "?")) ?
			ft_itoa(p->ret) : get_value(*p_env, d.var);
	if (j)
		d.tmp = ft_strjoin_free(ft_strsub(p->arg[i], 0, *j), d.key, 1, 0);
	else
		d.tmp = (d.key) ? ft_strdup(d.key) : ft_strdup("");
	if (d.p1 && d.p2 && d.p2 > d.p1)
		d.arg = ft_strjoin(d.tmp, &(p->arg[i][*j + 1]) + ft_strlen(d.var) + 2);
	else if (d.p3)
		d.arg = ft_strjoin(d.tmp, &(p->arg[i][*j + 1]) + ft_strlen(d.var));
	else
		d.arg = ft_strdup(d.tmp);
	ft_end_dollar(p, &d, i);
	*j = -1;
	return (p);
}
