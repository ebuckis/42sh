/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 13:55:04 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 11:17:49 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

/*
** Frees the linked list and reinits the informations.
*/

void	*free_slct(t_slct *lst, t_navig *info)
{
	t_slct	*tmp;
	t_slct	*tmp2;

	if (lst)
	{
		tmp = lst->next;
		while (tmp != lst)
		{
			tmp2 = tmp->next;
			ac_remove_elem(tmp);
			ft_memdel((void**)&tmp);
			tmp = tmp2;
		}
	}
	if (info->letters)
		ft_strdel(&info->letters);
	info->max_len = 0;
	info->nb_elem = 0;
	ft_memdel((void**)&lst);
	return (NULL);
}

/*
** Checks if the element of the list is an executable file.
*/

int		is_exe(char *name)
{
	struct stat	st;

	if (stat(name, &st) == -1)
		return (0);
	if (!S_ISDIR(st.st_mode) &&
	(st.st_mode & S_IXUSR || st.st_mode & S_IXGRP || st.st_mode & S_IXOTH))
		return (1);
	else
		return (0);
}

/*
** checks fi there are letters to be completed.
*/

int		contains_letters(char *name, char *letters)
{
	int	i;

	i = 0;
	if (!letters || !ft_strcmp(letters, ""))
		return (1);
	else
		while (letters[i])
		{
			if (name[i] != letters[i] && name[i] != ft_toupper(letters[i])
					&& name[i] != ft_tolower(letters[i]))
				return (0);
			i++;
		}
	return (1);
}

int		slct_current(t_slct *slct, t_navig *info)
{
	if (slct->current)
	{
		erase_prev(info);
		slct->current = 0;
		slct->next->current = 1;
		add_slct(slct->next, info);
		return (1);
	}
	return (0);
}

/*
** Completes the command line with the selected element.
*/

void	add_slct(t_slct *slct, t_navig *info)
{
	int	i;

	i = 0;
	if (info->letters)
		while (info->letters[i])
			i++;
	if (slct->name)
		while (slct->name[i])
		{
			ft_putchar(slct->name[i]);
			i++;
		}
	if (slct->is_dir)
		ft_putchar('/');
	tputs(tgetstr("sf", NULL), 1, ft_putchar_err);
	ft_move_to_xy(0, slct->y);
}
