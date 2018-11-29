/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_save_p_env.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 17:30:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 17:32:01 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

char	***ft_save_p_env(char ***p_env)
{
	static char		***p = NULL;

	if (p_env)
		p = p_env;
	return (p);
}

/*
** On enregistre le pointeur de env dans une statique
** pour y avoir acces quand on veut
*/
