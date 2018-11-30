/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_to_file.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 13:02:47 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 11:13:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"
#include "../../autocomp/includes/autocomp.h"

static void		ft_save_in_file(int fd, t_hist *h)
{
	if (!h)
		return ;
	ft_save_in_file(fd, h->next);
	ft_putendl_fd(h->str, fd);
}

void			ft_list_to_file(void)
{
	int		fd;
	t_hist	*h;
	char	*path;

	path = ft_get_hist_name();
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP |
	S_IROTH);
	if (fd == -1)
	{
		ft_strdel(&path);
		return ;
	}
	h = ft_close_hist(GET_HIST, NULL);
	ft_save_in_file(fd, h->next);
	ft_strdel(&path);
}
