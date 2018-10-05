/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_save_struct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 11:30:42 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/21 16:45:31 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_parser.h"

t_parse		**ft_save_struct(t_parse *parsing)
{
	static t_parse	*p = NULL;

	if (parsing)
		p = parsing;
	return (&p);
}

/*
** On enregistre la structure dans une statique
** pour y avoir acces quand on veut
*/
