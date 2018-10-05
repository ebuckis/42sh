/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_maj_win.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 19:00:09 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:29:21 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int		ft_win_some_line(t_navig *n, char *ret)
{
	if (n->y == n->y_size - 1)
	{
		if (!(ret = tgetstr("sf", NULL)))
			return (0);
		tputs(ret, 1, ft_putcharint);
		n->y_first--;
		n->y_start--;
	}
	n->y++;
	n->x = 0;
	ft_move_to_xy(0, n->y);
	return (1);
}

/*
** cas particulier si on se trouve tout en bas
*/

static int		ft_del_all(t_navig *n, int nb, char *ret)
{
	ft_get_size(&(n->x_size), &(n->y_size));
	if (!(ret = tgetstr("cd", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	ft_recup_pos(&(n->x_start), &(n->y_first));
	ft_putstr(n->prompt);
	if (!ft_no_new_name(n, n->prompt))
		return (0);
	ft_putstr(n->s);
	ft_recup_pos(&(n->x), &(n->y));
	ft_delta_line(n, nb);
	if ((nb - 1) % n->x_size == 0)
		if (!(ft_win_some_line(n, ret)))
			return (0);
	ft_recup_pos(&(n->x_len), &(n->y_len));
	ft_goto_i_from_end(n);
	return (1);
}

/*
** re-put de la line et repositionnement du curseur
*/

static int		ft_to_small(t_navig *n, char *ret)
{
	if (n->to_small == 0)
		n->to_small = 1;
	else
		return (1);
	if (!(ft_get_size(&(n->x_size), &(n->y_size))))
		return (0);
	if (!(ret = tgetstr("sc", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	if (!(ret = tgetstr("vi", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	ft_move_to_xy(0, 0);
	if (!(ret = tgetstr("cd", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	ft_putstr("resize me");
	return (1);
}

/*
** la fonction permet de suprimer ce qu'il y a l'ecran
** puis affiche 'resize me'
*/

static int		ft_win_line(t_navig *n)
{
	n->to_small = 0;
	if (!(n->tmp_char = tgetstr("rc", NULL)))
		return (0);
	tputs(n->tmp_char, 1, ft_putcharint);
	if (!(n->tmp_char = tgetstr("ve", NULL)))
		return (0);
	tputs(n->tmp_char, 1, ft_putcharint);
	ft_move_to_xy(0, 0);
	return (1);
}

int				ft_maj_win(t_navig *n)
{
	int		tmp;
	int		x_stmp;
	int		y_stmp;

	ft_get_size(&x_stmp, &y_stmp);
	n->tmp_int = ft_strlen(n->prompt) + ft_strlen(n->s) + 1;
	if (n->tmp_int > x_stmp * y_stmp)
		return (ft_to_small(n, n->tmp_char));
	if (n->to_small == 1 && !ft_win_line(n))
		return (0);
	else if (x_stmp < n->x_size && n->tmp_int >= n->x_size)
	{
		tmp = ((n->y - n->y_first) *
			(((n->x_size) / x_stmp) + 1) + (n->x / x_stmp)) - 1;
		ft_move_to_xy(0, n->y - tmp);
	}
	else if (x_stmp > n->x_size)
		ft_move_to_xy(0, n->y_first);
	else
	{
		n->y_first -= (n->y - y_stmp);
		ft_move_to_xy(0, n->y_first);
	}
	ft_del_all(n, n->tmp_int, n->tmp_char);
	return (1);
}

/*
** fonction qui recup la taille de la fenetre
** on se remet au debut a voir avec le y_first
** et on del et reafiche la line
** maj de x/y size, len...
** si fenetre trop petite message d'erreur
**
** envoie du char * du prompt
*/
