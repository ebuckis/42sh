/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:32:44 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 08:58:28 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** built-in echo : gere l'option -n (sans \n a la fin)
** affiche les arguments separes par des espaces
*/

static int	ft_verif_n(char *s)
{
	int		i;

	i = 1;
	if (!s[0] || s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int			ft_echo(char **arg)
{
	int		i;
	int		n;

	n = 0;
	if (arg[1])
		n = ft_verif_n(arg[1]);
	i = (n) ? 1 : 0;
	if (!arg[i + 1])
		ft_putchar('\n');
	while (arg[++i])
	{
		ft_putstr(arg[i]);
		if (arg[i + 1])
			ft_putchar(' ');
		else if (!n)
			ft_putchar('\n');
	}
	return (0);
}
