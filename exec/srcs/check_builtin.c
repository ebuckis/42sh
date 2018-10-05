/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_builtin.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:20:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 08:58:58 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** on check si le 1er arg de tab_commande est un builtin
*/

int		check_builtin(char **tab_com)
{
	if (tab_com && (ft_strequ(tab_com[0], "echo") || ft_strequ(tab_com[0], "cd")
		|| ft_strequ(tab_com[0], "setenv") || ft_strequ(tab_com[0], "unsetenv")
		|| ft_strequ(tab_com[0], "env") || ft_strequ(tab_com[0], "exit")
		|| ft_strequ(tab_com[0], "fg")))
		return (1);
	else
		return (0);
}

/*
** lance le builtin sans fork si pas de pipe seulement pour cd, setenv
** et unsetenv qui modifie l'env
*/

void	run_builtin(t_parse *p, char **tab_com, char ***p_env)
{
	if (tab_com)
	{
		if (ft_strequ(tab_com[0], "cd"))
			p->ret = ft_cd(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "setenv"))
			p->ret = ft_setenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unsetenv"))
			p->ret = ft_unsetenv(tab_com, p_env);
		ft_free_tab(&tab_com);
	}
}

/*
** lance le builtin apres fork et exit une fois le builtin fini
*/

void	run_builtin_fork(t_parse *p, char **tab_com, char ***p_env,
		int tab_pipe_i)
{
	if (tab_com)
	{
		if (ft_strequ(tab_com[0], "echo"))
			p->ret = ft_echo(tab_com);
		else if (ft_strequ(tab_com[0], "cd"))
			p->ret = ft_cd(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "setenv"))
			p->ret = ft_setenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unsetenv"))
			p->ret = ft_unsetenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "env"))
			p->ret = ft_env(p, tab_com, *p_env, tab_pipe_i);
		else if (ft_strequ(tab_com[0], "fg"))
			p->ret = ft_fg(p);
		else if (ft_strequ(tab_com[0], "exit"))
			;
	}
	exit(p->ret);
}
