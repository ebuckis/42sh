/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_struct.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:43:32 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 13:23:27 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Found offset if option -d
*/

static int		found_offset(t_opt_h **h, char **arg, int j, int i)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	if (ft_isdigit(arg[j][i + 1]) != 1)
	{
		if (arg[j + 1] == NULL)
		{
			ft_putstr_fd("42sh: history: -d: option requires an arguments\n", 2);
			history_usage();
			return (-10);
		}
		(*h)->offset = ft_atoi(arg[j + 1]);
		len = ft_strlen(arg[j + 1]);
		tmp = ft_strdup(arg[j + 1]);
	}
	else
	{
		tmp = ft_strsub(arg[j], i + 1, ft_strlen(arg[j]) - (i + 1));
		(*h)->offset = ft_atoi(tmp);
		len = ft_strlen(tmp);
	}
	j = (*h)->offset;
	i = 1;
	while (j > 10)
	{
		j /= 10;
		i++;
	}
	if (i != len)
	{
		history_out_str(tmp);
		ft_strdel(&tmp);
		return (-10);
	}
	ft_strdel(&tmp);
	return (i);
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
			if ((i += found_offset(h, arg, j, i)) < 0)
				return (1);
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
		else
		{
			printf("Option inconnu ? -> %s\n", arg[j] + i);
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
		if (arg[i] == NULL)
			return (0);
		if (arg[i][0] == 0)
			return (0);
		else if (arg[i][0] == '-')
		{
			if (insert_option(h, arg, i, 1) == 1)
				return (1);
		}
		else if (ft_isdigit(arg[i][0]) == 1)
			ft_print_history_len(ft_atoi(arg[i]));
		else
		{
			(*h)->filename = ft_strdup(arg[i]);
			return (0);
		}

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
