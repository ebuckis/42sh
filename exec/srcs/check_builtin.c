/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_builtin.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 18:20:01 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 12:03:07 by bpajot      ###    #+. /#+    ###.fr     */
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
		|| ft_strequ(tab_com[0], "setenv") || ft_strequ(tab_com[0], "set")
		|| ft_strequ(tab_com[0], "unsetenv") || ft_strequ(tab_com[0], "unset")
		|| ft_strequ(tab_com[0], "export") || ft_strequ(tab_com[0], "env")
		|| ft_strequ(tab_com[0], "exit") || ft_strequ(tab_com[0], "history")
		|| ft_strchr(tab_com[0], '=')))
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
		else if (ft_strequ(tab_com[0], "set"))
			p->ret = ft_set(p_env);
		else if (ft_strequ(tab_com[0], "export"))
			p->ret = ft_export(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unsetenv"))
			p->ret = ft_unsetenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unset"))
			p->ret = ft_unset(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "exit"))
			p->ret = ft_exit(tab_com, p_env);
		else if (ft_strchr(tab_com[0], '='))
			p->ret = ft_equal(p, tab_com, p_env, -1);
		ft_free_tab(&tab_com);
	}
}

/*
** lance le builtin apres fork et exit une fois le builtin fini
*/

void	run_builtin_fork(t_parse *p, char **tab_com, char ***p_env,
		int tab_pipe_i)
{
	int		ret;

	if (tab_com)
	{
		if (ft_strequ(tab_com[0], "echo"))
			p->ret = ft_echo(tab_com);
		else if (ft_strequ(tab_com[0], "cd"))
			p->ret = ft_cd(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "setenv"))
			p->ret = ft_setenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "set"))
			p->ret = ft_set(p_env);
		else if (ft_strequ(tab_com[0], "export"))
			p->ret = ft_export(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unsetenv"))
			p->ret = ft_unsetenv(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "unset"))
			p->ret = ft_unset(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "env"))
			p->ret = ft_env(p, tab_com, *p_env, tab_pipe_i);
		else if (ft_strequ(tab_com[0], "exit"))
			p->ret = ft_exit(tab_com, p_env);
		else if (ft_strequ(tab_com[0], "history"))
			p->ret = ft_history(tab_com, p_env);
		else if (ft_strchr(tab_com[0], '='))
			p->ret = ft_equal(p, tab_com, p_env, tab_pipe_i);
	}
	ret = p->ret;
	exit(ret);
}
