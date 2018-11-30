/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_default_edit.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 09:32:37 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 16:34:58 by kcabus      ###    #+. /#+    ###.fr     */
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
