/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_struct.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:43:32 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 16:42:52 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Delete Historique
*/

int				delete_history(void)
{
	t_hist		*h;

	h = NULL;
	// marche pas
	printf("DELETE HISTORY\n");
	//h = ft_close_hist(GET_HIST, NULL);
	//ft_free_hist(h);
	return (0);
}

/*
**	Insert les options dans la structure
*/

static int		insert_option(t_opt_h **h, char **arg, int j, int i)
{
	while (arg[j][i])
	{
		if (arg[j][i] == 'c')
			(*h)->c = 1;
		else if (arg[j][i] == 'd')
		{
			(*h)->d = 1;
			(*h)->di = i;
			(*h)->dj = j;
		}
		else if (arg[j][i] == 'a')
			(*h)->a = 1;
		else if (arg[j][i] == 'n')
			(*h)->n = 1;
		else if (arg[j][i] == 'r')
			(*h)->r = 1;
		else if (arg[j][i] == 'w')
			(*h)->w = 1;
		else if (arg[j][i] == 'p')
			(*h)->p = 1;
		else if (arg[j][i] == 's')
			(*h)->s = 1;
		else if (ft_isdigit(arg[j][i]) == 0)
		{
			history_invalid(arg[j], 1);
			history_usage();
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**	Search les options History
*/

int				search_options(t_opt_h **h, char **arg)
{
	int		i;

	i = 1;
	if (!arg)
		return (1);
	while (arg[i])
	{
		printf("arg[i] = %s\n", arg[i]);
		if (arg[i] == NULL)
			return (0);
		if (arg[i][0] == 0)
			return (0);
		else if (arg[i][0] == '-')
		{
			if (insert_option(h, arg, i, 1) == 1)
				return (1);
		}
		else if (ft_atoi(arg[i]) != 0 && (*h)->d == 0)
			ft_print_history_len(ft_atoi(arg[i]));
		else if (ft_atoi(arg[i]) != 0 && (*h)->d == 1)
			;
		else
		{
			history_invalid(arg[i], 2);
			return (1);
		}

		i++;
	}
	return (histo_suite(h, arg));
}

/*
**	Init struct for check options History
*/

t_opt_h			*check_hist(char **arg)
{
	t_opt_h 	*h;

	h = NULL;
	h = (t_opt_h *)malloc(sizeof(t_opt_h));
	if (h == NULL)
		return (NULL);
	h->c = 0;
	h->d = 0;
	h->di = 0;
	h->dj = 0;
	h->a = 0;
	h->n = 0;
	h->r = 0;
	h->w = 0;
	h->p = 0;
	h->s = 0;
	h->arg = 0;
	h->offset = 0;
	h->filename = NULL;
	h->histsize = info_histsize();
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
