/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_builtin.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:20:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 09:51:30 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** on check si le 1er arg de tab_commande est un builti qu'il ne faut pas forker
** si pas de pipe car il modifie l'env
** incompatible avec les redirections dans ce cas
*/

int		check_builtin2(char **tab_com)
{
	if (tab_com && (ft_strequ(tab_com[0], "cd") || ft_strequ(tab_com[0], "exit")
		|| ft_strequ(tab_com[0], "setenv") || ft_strequ(tab_com[0], "set")
		|| ft_strequ(tab_com[0], "unsetenv") || ft_strequ(tab_com[0], "unset")
		|| ft_strequ(tab_com[0], "export") || ft_strchr(tab_com[0], '=')))
		return (1);
	else
		return (0);
}
