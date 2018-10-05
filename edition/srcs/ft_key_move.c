/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_key_move.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 15:58:05 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 13:33:45 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int		ft_re_print_s(t_navig *n, int *y_add, int calc)
{
	char	*ret;

	ft_putstr(n->s);
	n->i = ft_strlen(n->s);
	ft_recup_pos(&(n->x), &(n->y));
	ft_recup_pos(&(n->x_len), &(n->y_len));
	if (calc % n->x_size == 0)
	{
		if (n->y == n->y_size - 1)
		{
			if (!(ret = tgetstr("sf", NULL)))
				return (0);
			tputs(ret, 1, ft_putcharint);
		}
		else
		{
			n->y++;
			n->y_len++;
		}
		n->x = 0;
		n->x_len = 0;
		(*y_add)++;
	}
	return (1);
}

static int		ft_maj_stuct_nav(t_navig *n, char *str)
{
	char	*ret;
	int		calc;
	int		y_add;
	int		y_old;

	ft_strdel(&(n->s));
	n->s = ft_strdup(str);
	ft_move_to_xy(n->x_start, n->y_start);
	if (!(ret = tgetstr("cd", NULL)))
		return (0);
	tputs(ret, 1, ft_putcharint);
	calc = ft_strlen(n->prompt) + ft_strlen(n->s);
	y_add = (calc / (n->x_size));
	y_add -= (calc % n->x_size == 0) ? 1 : 0;
	y_old = n->y_first;
	ft_re_print_s(n, &y_add, calc);
	if (y_old + y_add >= n->y_size)
	{
		n->y_first -= (y_old + y_add - n->y_size + 1);
		n->y_start -= (y_old + y_add - n->y_size + 1);
	}
	return (1);
}

/*
** permet de tout reafficher
** on del toute la ligne, et on reprint
** les differents calculs permettent de calculer la diff de ligne
** si par exemple on se trouve tout en bas
** et que l'hist tiens sur plusieurs lignes
*/

static void		ft_down_hist(t_navig *n)
{
	char	*str;

	str = NULL;
	str = ft_give_hist(-1, NULL);
	if (str)
	{
		ft_maj_stuct_nav(n, str);
		n->id_hist--;
	}
	else if (n->id_hist == 1)
	{
		ft_maj_stuct_nav(n, n->s_save);
		free(n->s_save);
		n->s_save = NULL;
		n->id_hist--;
	}
}

/*
** on a un retour -> maj de l'affichage
** sinon si on est dans l'historique mais que on a un retour null
** on se trouve sur la current string, donc on free la save
** et on fait une maj avec la current string
*/

static void		ft_up_hist(t_navig *n)
{
	char	*str;

	str = NULL;
	str = ft_give_hist(1, NULL);
	if (str)
	{
		if (n->id_hist == 0)
			n->s_save = ft_strdup(n->s);
		ft_maj_stuct_nav(n, str);
		n->id_hist++;
	}
}

/*
** on catch le hist precedent
** on place la curent string dans une save uniquement si on est tout en bas
** d'ou l'utilité du id_hist
** et on met a jour l'affichage avec maj_struct_nav
*/

int				ft_key_move(t_navig *n, char *buf)
{
	if (KEY_CODE_UP)
		ft_up_hist(n);
	else if (KEY_CODE_DOWN)
		ft_down_hist(n);
	else if (KEY_CODE_LEFT)
		ft_x_change(n, MOVE_LEFT);
	else if (KEY_CODE_RIGHT)
		ft_x_change(n, MOVE_RIGHT);
	else if (KEY_CODE_END)
	{
		n->x = n->x_len;
		n->y = n->y_len;
		n->i = ft_strlen(n->s);
	}
	else if (KEY_CODE_HOME)
	{
		n->x = n->x_start;
		n->y = n->y_start;
		n->i = 0;
	}
	return (1);
}

/*
** appel aux fonctions, les defines parlent d'eux memes
*/
