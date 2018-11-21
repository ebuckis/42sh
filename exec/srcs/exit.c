/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exit.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/06 16:15:29 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 16:20:12 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

static void		ft_special_free(char ***p_env)
{
	ft_free_tab(&p_env[0]);
	ft_free_tab(&p_env[1]);
	ft_memdel((void**)&p_env);
}

int				ft_exit(char **arg, char ***p_env)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (arg[1])
	{
		while ((i == 0 && arg[1][i] == '-') || ft_isdigit(arg[1][i]))
			i++;
		if (!arg[1][i])
			ret = (unsigned char)ft_atoi(arg[1]);
		else
		{
			ft_putstr_fd("21sh: exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ret = 255;
		}
	}
	ft_printf("exit\n");
	ft_special_free(p_env);
	ft_free_tab(&arg);
	ft_close_hist(CLOSE_HIST, NULL);
	exit(ret);
}
