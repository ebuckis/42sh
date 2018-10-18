/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_ac.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 13:12:46 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 13:13:06 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

int	ft_putchar_err(int c)
{
	return (write(1, &c, 1));
}

void	free_tab(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		ft_strdel(&table[i]);
		i++;
	}
	free(table);
}

char	last_char(char *str)
{
	if (!str || !ft_strcmp(str, ""))
		return (0);
	else
		return (str[ft_strlen(str) - 1]);
}
