/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 13:39:56 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 08:17:15 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static char	*ft_get_occ(t_navig *n, int (*func)(t_hist *, char *))
{
	t_hist	*h;

	h = ft_close_hist(GET_HIST, NULL);
	while (h)
	{
		if (h->str && func(h, n->pattern))
			return (ft_strdup(h->str));
		h = h->next;
	}
	return (NULL);
}

static int	ft_get_by_id(t_hist *h, char *s2)
{
	int		nb;

	if (!h->str || !s2)
		return (0);
	nb = ft_atoi(s2);
	if (nb <= 0)
		return (0);
	if (h->id == nb)
		return (1);
	return (0);
}

static int	ft_get_by_last_id(t_hist *h, char *s2)
{
	int		nb;

	if (!h->str || !s2)
		return (0);
	nb = ft_atoi(s2);
	if (nb < 0)
		nb *= -1;
	if (g_nav.max_id - nb <= 0)
		return (0);
	if (h->id == g_nav.max_id - nb)
		return (1);
	return (0);
}

static int	ft_get_by_occur(t_hist *h, char *s2)
{
	int		i;

	i = 0;
	if (h->str || !s2)
		return (0);
	while (h->str[i] && s2[i])
	{
		if (h->str[i] != s2[i])
			return (0);
		i++;
	}
	if (!s2[i])
		return (1);
	return (0);
}

int			ft_replace_line(t_navig *n, int *pos, int id)
{
	char	*str;
	int		ret;

	ret = 1;
	str = NULL;
	if (id == LAST_ID_NUM)
		str = ft_get_occ(n, &ft_get_by_last_id);
	else if (id == ID_NUM)
		str = ft_get_occ(n, &ft_get_by_id);
	else if (id == OCCURRENCE)
		str = ft_get_occ(n, &ft_get_by_occur);
	if (str)
		ret = ft_replace_s(str, n, *pos);
	else
		n->err = id * -1;
	ft_strdel(&n->pattern);
	*pos = ret + *pos;
	return (0);
}
