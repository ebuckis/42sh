/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_to_lst.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 17:30:05 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:43:40 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

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
// a delete