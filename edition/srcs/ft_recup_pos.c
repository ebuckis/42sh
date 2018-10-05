/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_pos.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 15:50:50 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 16:30:37 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void	ft_recup_pos(int *x, int *y)
{
	char	pos[20];
	char	*str;
	int		i;

	i = 0;
	str = "\033[6n";
	ft_bzero(pos, 20);
	ft_printf("%s", str);
	read(0, pos, 20);
	*y = ft_atoi(pos + 2) - 1;
	while (pos[i] && pos[i] != 59)
		i++;
	*x = ft_atoi(pos + i + 1) - 1;
}

/*
** permet de recuperer la position on x et y du curseur sur le terminal
*/
