/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_struct.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:43:32 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 14:20:53 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Search les options History
*/

int			search_options(t_opt_h **h, char **arg)
{
	int		i;

	i = 1;
	if (!arg)
		return (1);
	if (ft_strcmp(arg[0], "history") != 0)
		return (1);
	while (arg[i])
	{
		i++;
	}
	return (0);
}

/*
**	Init struct for check options History
*/

t_opt_h		*check_hist(char **arg)
{
	t_opt_h 	*h;

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
	h->offset = 0;
	h->filename = NULL;
	h->arg = NULL;
	if (seach_options(&h, arg) == 1)
	{
		h = delete_struct_hist(h);
		return (NULL);
	}
	return (h);
}

/*
**	Delete Struct 
*/

t_opt_h		*delete_struct_hist(t_opt_h *h)
{
	if (!h)
		return (NULL);
	ft_strdel(&h->filename);
	ft_free_tab(&(h->arg));
	free(h);
	h = NULL;
	return (NULL);
}
