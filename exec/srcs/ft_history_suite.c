/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_suite.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 14:10:29 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 10:46:46 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Option -a :
**	Ajouter les nouvelles lignes d'historique
**	(lignes d'historique entrées depuis début de la session Bash en cours)
**	dans le fichier d’historique.
*/

static int	histo_a(t_opt_h *h, int fd)
{
	t_hist	*his;

	his = NULL;
	if (h->filename == NULL)
		ft_list_to_file();
	else
	{
		his = ft_close_hist(GET_HIST, NULL);
		if ((fd = open(h->filename, O_RDONLY)) < 0)
			return (1);
		while (his->next)
			his = his->next;
		while (his->prev)
		{
			if (his->current == 1)
			{
				ft_putstr_fd(his->str, fd);
				ft_putstr_fd("\n", fd);
			}
			his = his->prev;
		}
		close(fd);
	}
	return (0);
}

/*
**	Option -n :
**	Ajoute les lignes d'historique non lues à partir du fichier d'historique.
**	Ce sont des lignes annexées à la historique depuis le début de la session
**	Bash en cours.
*/

static int	histo_n(t_opt_h *h)
{
	(void)h;
	ft_list_to_file();
	return (0);
}

/*
**	Option -r:
**	Lit le fichier d'historique actuel et ajoute son contenu à la liste
**	d'historique.
*/

static int	histo_r(t_opt_h *h, int fd)
{
	char	*line;
	char	*path;

	line = NULL;
	path = NULL;
	if (h->filename == NULL)
	{
		path = ft_get_hist_name();
		fd = open(path, O_RDONLY);
		ft_strdel(&path);
	}
	else
		fd = open(h->filename, O_RDONLY);
	if (fd == -1)
		return (1);
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "") != 0)
			ft_add_hist(line, 0, 0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (0);
}

/*
**	Option -w:
**	Ecrit l'historique actuel dans le fichier historique
**	(filename ou celui par default).
*/

static int	histo_w(t_opt_h *h)
{
	t_hist	*his;
	int		fd;

	if (h->filename == NULL)
	{
		ft_list_to_file();
		return (0);
	}
	his = ft_close_hist(GET_HIST, NULL);
	fd = open(h->filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (1);
	while (his)
	{
		ft_putstr_fd(his->str, fd);
		ft_putstr_fd("\n", fd);
		his = his->next;
	}
	close(fd);
	return (0);
}

/*
**	Suite historique
*/

int			histo_suite(t_opt_h *h, char **arg)
{
	int		ret;

	ret = -1;
	if (h->c == 1)
		return (0);
	if (h->d == 1)
		ret = delete_line_history(h->offset);
	if (h->a == 1)
		ret = histo_a(hi, 0);
	if (h->n == 1)
		ret = histo_n(h);
	if (h->r == 1)
		ret = histo_r(h, 0);
	if (h->w == 1)
		ret = histo_w(h);
	if (h->p == 1)
		ret = histo_p(h, arg);
	if (h->s == 1)
		ret = histo_s(h, arg);
	if (ret == -1)
	{
		history_invalid(h->filename, 2);
		return (1);
	}
	return (ret);
}
