/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_copy_paste.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 08:27:26 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 14:04:16 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int		ft_cutstr_home(t_navig *n, char **copy, int nb)
{
	char	buf[5];
	int		i;

	ft_bzero(buf, 5);
	buf[0] = 127;
	if (n->i != 0)
	{
		ft_strdel(copy);
		i = n->i;
		if (!(*copy = ft_strnew(n->i)))
			return (0);
		*copy = ft_strncpy(*copy, n->s, n->i);
		if (nb == 1)
		{
			while (n->i)
				ft_key_code(n, buf);
		}
	}
	else
	{
		if (!ft_ring_the_bell())
			return (0);
	}
	return (1);
}

/*
** on remplit copy
** on del jusqu'au debut depuis la pos de i
*/

static int		ft_cutstr_end(t_navig *n, char **copy, int nb)
{
	int		i;

	if (n->i != (int)ft_strlen(n->s))
	{
		ft_strdel(copy);
		i = n->i;
		if (!(*copy = ft_strnew(ft_strlen(n->s) - n->i)))
			return (0);
		while (n->s[i])
		{
			(*copy)[i - n->i] = n->s[i];
			i++;
		}
		if (nb == 1)
			ft_del_end_to_i(n);
	}
	else if (!ft_ring_the_bell())
		return (0);
	return (1);
}

/*
** on remplit copy
** on va a la fin
** on boucle sur s pour del jusqu'a la position de i
** si on est deja a la fin -> bell
*/

static int		ft_small_verif(t_navig *n, char *copy)
{
	int		np;
	int		ns;
	int		nc;

	np = (n->prompt) ? ft_strlen(n->prompt) : 0;
	ns = (n->s) ? ft_strlen(n->s) : 0;
	nc = (copy) ? ft_strlen(copy) : 0;
	if (np + ns + nc >= n->y_size * n->x_size)
		return (0);
	else
		return (1);
}

/*
** verif pour voir si ca rentre !
*/

static int		ft_paste(t_navig *n, char *copy)
{
	char	buf[5];
	int		i;

	i = 0;
	ft_bzero(buf, 5);
	if (copy && ft_small_verif(n, copy))
	{
		while (copy[i])
		{
			buf[0] = copy[i];
			ft_key_code(n, buf);
			i++;
		}
	}
	else
	{
		if (!ft_ring_the_bell())
			return (0);
	}
	return (1);
}

/*
** on boucle sur s pour print tous les caracteres
** bell si ca ne rentre pas ou si copy != NULL
*/

int				ft_copy_paste(t_navig *n, char *buf, int fr)
{
	static char	*copy = NULL;

	if (fr == 1)
	{
		ft_strdel(&copy);
		return (1);
	}
	if (KEY_CTRL_U)
		ft_cutstr_home(n, &copy, 1);
	else if (KEY_CTRL_K)
		ft_cutstr_end(n, &copy, 1);
	else if (KEY_CTRL_E)
		ft_cutstr_home(n, &copy, 0);
	else if (KEY_CTRL_W)
		ft_cutstr_end(n, &copy, 0);
	else if (KEY_CTRL_T)
		ft_paste(n, copy);
	return (1);
}

/*
** le free de copy s'efectue depuis ft_close_hist
*/
