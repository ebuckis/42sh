/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dollar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 14:11:36 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 12:54:22 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

char			*get_value(char ***p_env, char *key, int start, int end)
{
	int		i;
	int		j;
	char	*tmp;

	i = start - 1;
	while (++i <= end)
	{
		j = -1;
		while (p_env[i] && p_env[i][++j])
		{
			tmp = ft_strjoin(key, "=");
			if (ft_strnequ(p_env[i][j], tmp, ft_strlen(tmp)))
			{
				ft_memdel((void**)&tmp);
				return (ft_strdup(p_env[i][j] + ft_strlen(key) + 1));
			}
			ft_memdel((void**)&tmp);
		}
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
	char *next_tilde;

	next_dollar = ft_strchr(str, '$');
	next_sp = ft_strchr(str, ' ');
	next_nl = ft_strchr(str, '\n');
	next_tilde = ft_strchr(str, '~');
	p = NULL;
	if (next_dollar || next_sp || next_nl || next_tilde)
	{
		p = (next_dollar) ? next_dollar : p;
		p = (next_sp && (!p || next_sp < p)) ? next_sp : p;
		p = (next_nl && (!p || next_nl < p)) ? next_nl : p;
		p = (next_tilde && (!p || next_tilde < p)) ? next_tilde : p;
	}
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
			ft_itoa(p->ret) : get_value(p_env, d.var, 0, 1);
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
