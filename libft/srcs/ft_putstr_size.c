/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_size.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 09:26:14 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 08:49:54 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putstr_size(char *str)
{
	if (str)
		return (write(1, str, ft_strlen(str)));
	else
		return (-1);
}

int		ft_putstr_sizel(char *str, int i)
{
	if (str && i >= 0)
		return (write(1, str, i));
	else
		return (-1);
}
