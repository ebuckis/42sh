/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_s.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 16:01:31 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 11:20:49 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int		ft_replace_s(char *s, t_navig *n, int pos)
{
	char	**string;
	char	*tmp;
	int		nb;

	string = (char **)malloc(sizeof(char *) * 4);
	string[0] = ft_strsub(n->s, 0, (size_t)pos);
	string[1] = s;
	string[2] = ft_strdup(n->s + pos + strlen(n->pattern) + 1);
	string[3] = NULL;
	tmp = ft_strjoin(string[0], (char *)string[1]);
	nb = ft_strlen(tmp);
	ft_strdel(&(n->s));
	n->s = ft_strjoin(tmp, string[2]);
	ft_free_tab(&string);
	ft_strdel(&tmp);
	return (nb);
}
