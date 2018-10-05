/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_heredoc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/20 12:06:12 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:43:21 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

static void	ft_replace_arg(t_parse *p, int j)
{
	int		len;
	char	*tmp;

	if (!p->hdoc[j])
		p->hdoc[j] = ft_strdup("");
	len = ft_strlen(p->hdoc[j]);
	ft_strdel(&(p->arg[p->i]));
	p->arg[p->i] = ft_strdup(p->hdoc[j]);
	tmp = ft_strnew(len);
	tmp[len] = '\0';
	while (len)
	{
		len--;
		tmp[len] = HEREDOC;
	}
	ft_strdel(&(p->arg_id[p->i]));
	p->arg_id[p->i] = tmp;
}

/*
** permet de remplacer les arguments par les entrees
*/

static int	ft_save_hdoc(t_parse *p, int j)
{
	char	*stop;
	char	*line;
	char	*tmp;

	p->i++;
	stop = p->arg[p->i];
	while (101)
	{
		line = ft_edition("heredoc > ");
		if (g_nav.err == SIG_CTRLD)
			break ;
		if (line && ft_strcmp(stop, line) == 0)
			break ;
		tmp = ft_strjoin_del(line, "\n");
		line = ft_strjoin(p->hdoc[j], tmp);
		if (p->hdoc[j])
			free(p->hdoc[j]);
		ft_strdel(&tmp);
		p->hdoc[j] = line;
	}
	ft_strdel(&line);
	ft_replace_arg(p, j);
	return (1);
}

/*
** boucle jusqu'a ce aur line == stop
** quand c'est le cas on remplace l'argument qui stop le heredoc
** par les char* rentrés join par des '\n'
*/

int			ft_heredoc(t_parse *p)
{
	int		j;

	j = 0;
	p->i = 0;
	p->hdoc = (char **)malloc(sizeof(char *) * (p->nb_hdoc + 1));
	while (j <= p->nb_hdoc)
	{
		p->hdoc[j] = NULL;
		j++;
	}
	j = 0;
	p->hdoc[p->nb_hdoc] = NULL;
	while (p->arg[p->i] && p->arg_id[p->i])
	{
		if (p->arg_id[p->i][0] == HEREDOC)
		{
			ft_save_hdoc(p, j);
			j++;
		}
		p->i++;
	}
	return (1);
}

/*
** gestion des heredoc, creation d'un tableau dans la struct p
*/
