/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tilde_dollar.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 12:03:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 15:50:59 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

char			*ft_strjoin_free(char *line1, char *line2, int i, int j)
{
	char *tmp;

	tmp = ft_strjoin(line1, line2);
	if (i)
		ft_memdel((void**)&line1);
	if (j)
		ft_memdel((void**)&line2);
	return (tmp);
}

/*
** remplacement de la string
*/

static t_parse	*ft_tilde(t_parse *p, int i)
{
	char	*home;
	char	*tmp;

	home = getenv("HOME");
	if (home)
	{
		tmp = ft_strjoin_free(home, &(p->arg[i][1]), 0, 0);
		ft_memdel((void**)&(p->arg[i]));
		p->arg[i] = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&(p->arg_id[i]));
		p->arg_id[i] = ft_memalloc(ft_strlen(p->arg[i]) + 1);
		ft_bzero((void*)p->arg_id[i], ft_strlen(p->arg[i]) + 1);
		ft_memset((void*)p->arg_id[i], WORD, ft_strlen(p->arg[i]));
	}
	return (p);
}

t_parse			*ft_tilde_dollar(t_parse *p, int i, char ***p_env)
{
	int		j;

	i--;
	if (p->arg)
	{
		while (p->arg[++i] && p->arg_id[i][0] < PIPE)
		{
			if (p->arg[i][0] == '~' && p->arg_id[i][0] == WORD)
				ft_tilde(p, i);
			if (ft_strchr(p->arg[i], '$'))
			{
				j = -1;
				while (p->arg[i][++j])
				{
					if (p->arg[i][j] == '$' && p->arg[i][j + 1] &&
						(p->arg_id[i][j] == WORD || p->arg_id[i][j] ==
						DOUBLE_QUOTE))
						p = ft_dollar(p, i, j, p_env);
				}
			}
		}
	}
	return (p);
}

/*
** on boucle sur les arguments afin de remplacer un ~ ou encore un $
** par les variables associees
*/
