/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_nav.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 15:48:03 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 11:56:18 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

int			ft_no_new_name(t_navig *n, char *p)
{
	char	*ret;

	ft_recup_pos(&(n->x_start), &(n->y_start));
	if (ft_strlen(p) % n->x_size == 0)
	{
		n->x_start = 0;
		if (n->y_first == n->y_size - 1)
		{
			if (!(ret = tgetstr("sf", NULL)))
				return (0);
			tputs(ret, 1, ft_putcharint);
			n->y_first--;
			n->y_start = n->y_size - 1;
		}
		else
			n->y_start++;
	}
	else if (ft_strlen(p) / n->x_size != 0)
		n->y_first--;
	n->x = n->x_start;
	n->y = n->y_start;
	return (1);
}

/*
** prise en compte des valeurs initiales
** pour bien commencer cette superbe edition
*/

int			ft_init_nav(t_navig *n, char *p)
{
	int		x_tmp;

	if (!(ft_get_size(&(n->x_size), &(n->y_size))))
		return (0);
	ft_recup_pos(&x_tmp, &(n->y_first));
	ft_recup_pos(&x_tmp, &(n->y_first));
	ft_putstr(p);
	n->to_small = 0;
	n->prompt = p;
	if (!ft_no_new_name(n, p))
		return (0);
	n->i = 0;
	n->x_len = n->x_start;
	n->y_len = n->y_start;
	if (!(n->s = ft_strdup("\0")))
		return (0);
	n->s_save = NULL;
	n->id_hist = 0;
	if (!(ft_open_hist()))
		return (0);
	if (!(ft_move_to_xy(n->x_start, n->y_start)))
		return (0);
	n->err = 1;
	n->statut = 1;
	return (1);
}

/*
** init de la structure nav (variable globale)
** cas particulier quand le prompt depasse la taille du terminal
*/
