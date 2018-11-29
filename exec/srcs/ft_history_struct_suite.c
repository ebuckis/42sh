/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_struct_suite.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:42:17 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 12:53:11 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Init struct for check options History
*/

t_opt_h			*check_hist(char **arg)
{
	t_opt_h		*h;

	h = NULL;
	h = (t_opt_h *)malloc(sizeof(t_opt_h));
	if (h == NULL)
		return (NULL);
	h->c = 0;
	h->d = 0;
	h->a = 0;
	h->n = 0;
	h->r = 0;
	h->w = 0;
	h->p = 0;
	h->s = 0;
	h->print_line = 0;
	h->offset = 0;
	h->filename = NULL;
	if (search_options(&h, arg) == 1)
	{
		h = delete_struct_hist(h);
		return (NULL);
	}
	return (h);
}

/*
**	Delete Struct
*/

t_opt_h			*delete_struct_hist(t_opt_h *h)
{
	if (!h)
		return (NULL);
	ft_strdel(&h->filename);
	free(h);
	h = NULL;
	return (NULL);
}
