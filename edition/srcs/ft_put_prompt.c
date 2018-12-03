/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_put_prompt.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 14:59:18 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 15:21:28 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

void	ft_put_prompt(char *deb, char *prompt)
{
	if (!deb)
	{
		ft_putstr(prompt);
		return ;
	}
	ft_putstr(deb);
	ft_putstr(prompt);
	ft_putstr(RESET);
}
