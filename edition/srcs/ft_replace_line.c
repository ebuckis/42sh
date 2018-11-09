/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_replace_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 13:39:56 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 15:39:57 by kcabus      ###    #+. /#+    ###.fr     */
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

//	//dprintf(2, "__Dans %s, s2 : %s__\n", __func__, s2);
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

//	//dprintf(2, "__Dans %s, s2 : %s__\n", __func__, s2);
	if (!h->str || !s2)
		return (0);
	//dprintf(2, "__1__\n");
	nb = ft_atoi(s2);
	if (nb < 0)
		nb = (nb * -1) - 1;
	//dprintf(2, "__max : |%d| et nb : |%d|__\n", g_nav.max_id, nb);
	if (g_nav.max_id - nb <= 0)
		return (0);
	//dprintf(2, "__2__\n");
	if (h->id == g_nav.max_id - nb)
		return (1);
	//dprintf(2, "__3__\n");
	return (0);
}

static int	ft_get_by_occur(t_hist *h, char *s2)
{
	int		i;

//	//dprintf(2, "__Dans %s, s2 : %s__\n", __func__, s2);
	i = 0;
	if (!h->str || !s2)
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

int			ft_message_err(t_navig *n)
{
	ft_putstr_fd("\n42sh : !", 2);
	ft_putstr_fd(n->pattern, 2);
	ft_putendl_fd(": event not found\n", 2);
	ft_strdel(&n->pattern);
	return (-1);
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
	//dprintf(2, "__Dans %s, str : %s__\n", __func__, str);
	if (str)
		*pos = ft_replace_s(str, n, *pos);
	else
		return (ft_message_err(n));
	ft_strdel(&n->pattern);
	//*pos = ret + *pos;
	return (0);
}
