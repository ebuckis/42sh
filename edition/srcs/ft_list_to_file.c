/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_to_file.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 13:02:47 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 10:26:30 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_editon.h"


void        ft_list_to_file(t_navig *h)
{
    char    *line;
    char                
    int     fd;
    int     id;

    fd = open(HIST_FILE, O_RDONLY);
    if (fd == -1)
        return ;
    while (get_next_line(fd, &line))
    {
        ft_add_hist
    }
}