/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_file_to_list.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 11:04:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 11:30:04 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void		ft_file_to_list(void)
{
	char	*line;
	int		fd;

	fd = open(HIST_FILE, O_RDONLY);
	if (fd == -1)
	{
		printf("pas OK\n");
		return ;
	}
		printf("OK\n");
	while (get_next_line(fd, &line))
	{
		printf("line : %s\n", line);
		ft_add_hist(line);
		ft_strdel(&line);
	}
	close(fd);
}
