/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_backspaces.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 14:54:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/05 14:54:20 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

int			add_bs(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' && str[i - 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}

static int	find_spaces(int i, char **str, char **tmp)
{
	while ((*str)[i] && (*str)[i] != ' ')
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] && (*str)[i + 1] == ' ')
		{
			(*tmp)[i] = (*str)[i];
			i = i + 1;
		}
		(*tmp)[i] = (*str)[i];
		i = i + 1;
	}
	return (i);
}

void		add_bs_in_str(char **str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!(tmp = (char*)malloc(ft_strlen(*str) + 2)))
		return ;
	i = find_spaces(i, str, &tmp);
	tmp[i] = '\\';
	tmp[i + 1] = ' ';
	i += 2;
	j = i - 1;
	while ((*str)[j])
	{
		tmp[i] = (*str)[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
}
