/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fg.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 13:26:26 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 14:35:32 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** built-in fg : reveille le processus endormi enregistre dans child->pid_t
** suite a un Ctrl-Z
*/

int		ft_fg(t_parse *p)
{
	if (p->child_pid)
	{
		kill(p->child_pid, 19);
		return (0);
	}
	else
		return (1);
}
