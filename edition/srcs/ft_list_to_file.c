/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_to_file.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 13:02:47 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/22 14:12:44 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_editon.h"

#define HIST_FILE "~/.42sh_history"

void        ft_list_to_file(t_navig *l)
{
    char    *line;
    int     fd;

    fd = open(HIST_FILE, O_RDONLY);
    if (fd == -1)
        return ;
    while (get_next_line(fd, &line))
    {
        ft_add_hist
    }
}