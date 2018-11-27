/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   infos_hist.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:36:13 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 14:57:33 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
**	Return HISTSIZE
*/

int			info_histsize(void)
{
	int		h;

	// remettre a 500
	// 25 pour debug
	h = 25;
	return (h);
}

/*
**	Return HISTFILE
*/

int			info_histfile(void)
{
	int		h;

	h = 500;
	return (h);
}

/*
**	Return HISTFILESIZE
*/

int			info_histfilesize(void)
{
	int		h;

	h = 500;
	return (h);
}
