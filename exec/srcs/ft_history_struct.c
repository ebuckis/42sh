/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_struct.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:43:32 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 16:48:12 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Print Usage
*/
/*
static int		history_usage(char err)
{
	ft_putstr_fd("42sh: history: -", 2);
	ft_putchar_fd(err, 2);
	ft_putstr_fd("\nhistory: usage: history [-c] [-d offset] [n] or ", 2);
	ft_putstr_fd("history -awrn [filename] or history -ps [arg...]\n", 2);
	return (1);
}
*/
/*
**	Check si argument valide
*/

static int		delete_history(void)
{
	printf("DELETE FULL HISTORIQUE\n");
	return (0);
}

/*
**	Insert les options dans la structure
*/

static int		insert_option(t_opt_h **h, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 'c')
			return (delete_history());
		else if (str[i] == 'd')
			return (delete_line_history(h, str, i));
		else if (str[i] == 'a')
			(*h)->a = 1;
		else if (str[i] == 'n')
			(*h)->n = 1;
		else if (str[i] == 'r')
			(*h)->r = 1;
		else if (str[i] == 'w')
			(*h)->w = 1;
		else if (str[i] == 'p')
			(*h)->p = 1;
		else if (str[i] == 's')
			(*h)->s = 1;
		else
			printf("JE FAIS QUOI ?\n");
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
		if (arg[i] == NULL)
			return (0);
		if (arg[i][0] == '-')
		{
			if (insert_option(h, arg[i], 1) == 1)
				return (1);
		}
		else if ((*h)->p == 1 || (*h)->s == 1)
			(*h)->arg = i;
		else 
			(*h)->filename = ft_strdup(arg[i]);
		i++;
	}
	return (0);
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
