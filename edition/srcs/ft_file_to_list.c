/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_file_to_list.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 11:04:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 10:59:57 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"
#include "../../autocomp/includes/autocomp.h"

char	*ft_get_hist_name(void)
{
	char	*name;
	char	*s;

	s = getenv("HOME");
	if (!s)
		return (ft_strjoin("/tmp/", HIST_FILE));
	s = ft_strjoin(s, "/");
	name = ft_strjoin_del(s, HIST_FILE);
	return (name);
}

void	ft_file_to_list(void)
{
	char	*line;
	char	*path;
	int		fd;

	line = NULL;
	path = ft_get_hist_name();
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_strdel(&path);
		return ;
	}
	while (get_next_line(fd, &line))
	{
		ft_add_hist(line, 0, 0);
		ft_strdel(&line);
	}
	ft_strdel(&path);
	close(fd);
}
