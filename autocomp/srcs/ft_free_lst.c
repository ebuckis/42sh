/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_lst.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 16:09:22 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:37:36 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

void	*free_lst(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	ft_memdel((void**)&lst->content);
	free_lst(lst->next);
	ft_memdel((void**)&lst);
	return (NULL);
}
