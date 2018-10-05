/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_default_edit.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 09:32:37 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 14:23:40 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

struct termios		ft_default_edit(struct termios term)
{
	if (tcgetattr(0, &term) == -1)
		return (term);
	term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (term);
	return (term);
}

/*
** Reinitialisation du terminal
*/
