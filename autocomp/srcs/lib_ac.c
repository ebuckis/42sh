/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lib_ac.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 13:12:46 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 16:00:44 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

int		ft_putchar_err(int c)
{
	return (write(1, &c, 1));
}

char	last_char(char *str)
{
	if (!str || !ft_strcmp(str, ""))
		return (0);
	else
		return (str[ft_strlen(str) - 1]);
}

t_list	*tab_to_lst(char **table)
{
	t_list	*ret;
	t_list	*tmp;
	int		i;

	i = 0;
	if (!table[0])
		return (NULL);
	ret = ft_lstnew(NULL, 0);
	tmp = ret;
	while (table[i])
	{
		tmp->content = ft_strdup(table[i]);
		tmp->next = ft_lstnew(NULL, 0);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}
