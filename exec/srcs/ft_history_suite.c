/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_history_suite.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 14:10:29 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 11:10:22 by yoginet     ###    #+. /#+    ###.fr     */
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

static int	histo_a(t_opt_h *h)
{
	// manque booleen pour savoir qu'elles sont les lignes de la session en cour
	printf("OPTION a !\n");
	printf("filename -> %s\n", h->filename);
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
	t_hist	*his;

	his = ft_close_hist(CLOSE_HIST, NULL);
	printf("OPTION n !\n");
	printf("filename -> %s\n", h->filename);
	return (0);
}

/*
**	Option -r:
**	Lit le fichier d'historique actuel et ajoute son contenu à la liste d'historique.
*/

static int	histo_r(t_opt_h *h)
{
	t_hist	*his;

	printf("OPTION r !\n");
	printf("filename -> %s\n", h->filename);
	// si filename != NULL
	// il faut read filename et pas le fichier de .bashrc
	his = ft_close_hist(CLOSE_HIST, NULL);
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

int			histo_suite(t_opt_h *h)
{
	int		ret;

	ret = -1;
	if (h->d == 1)
		ret = delete_line_history(h->offset);
	if (h->c == 1)
		ret = delete_history();
	if (h->a == 1)
		ret = histo_a(h);
	if (h->n == 1)
		ret = histo_n(h);
	if (h->r == 1)
		ret = histo_r(h);
	if (h->w == 1)
		ret = histo_w(h);
	if (ret == -1)
	{
		history_invalid(h->filename, 2);
		return (1);
	}
	return (ret);
}
