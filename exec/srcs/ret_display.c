/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ret_display.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 11:37:28 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 16:12:44 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** affichage des signaux qui interrompe un processus
*/

static void		ft_ret_display_signal2(int signal)
{
	if (signal == 8)
		ft_putstr_fd("Floating point exception: ", 2);
	else if (signal == 9)
		ft_putstr_fd("Killed: ", 2);
	else if (signal == 10)
		ft_putstr_fd("Bus error: ", 2);
	else if (signal == 11)
		ft_putstr_fd("Segfault: ", 2);
	else if (signal == 12)
		ft_putstr_fd("Bad system call: ", 2);
	else if (signal == 13)
		ft_putstr_fd("Broken Pipe: ", 2);
	else if (signal == 14)
		ft_putstr_fd("Alarm: ", 2);
	else if (signal == 15)
		ft_putstr_fd("Terminated: ", 2);
	else if (signal == 17 || signal == 18)
		ft_putstr_fd("Stopped: ", 2);
}

static void		ft_ret_display_signal3(int pid)
{
	ft_putstr_fd("pid: ", 2);
	ft_putnbr_fd(pid, 2);
	ft_putstr_fd("\t", 2);
}

static void		ft_ret_display_signal4(int signal)
{
	ft_putstr_fd("Signal = ", 2);
	ft_putnbr_fd(signal, 2);
	ft_putstr_fd("\n", 2);
}

/*
** affichage des signaux qui interrompe un processus
*/

static void		ft_ret_display_signal(pid_t pid, int status, int stop)
{
	int		signal;

	signal = (stop) ? WSTOPSIG(status) : WTERMSIG(status);
	if (signal > 0 && signal < 32)
	{
		ft_ret_display_signal3(pid);
		if (signal == 1)
			ft_putstr_fd("Hangup: ", 2);
		else if (signal == 2)
			ft_putstr_fd("Interupt: ", 2);
		else if (signal == 3)
			ft_putstr_fd("Quit: ", 2);
		else if (signal == 4)
			ft_putstr_fd("Illegal instruction: ", 2);
		else if (signal == 5)
			ft_putstr_fd("Trace trap: ", 2);
		else if (signal == 6)
			ft_putstr_fd("Abort trap: ", 2);
		else if (signal == 7)
			ft_putstr_fd("EMT trap: ", 2);
		else
			ft_ret_display_signal2(signal);
		ft_ret_display_signal4(signal);
	}
}

/*
** gestion des signaux de retour des processus pour les mettre dans p->ret
*/

int				ft_ret_display(t_parse *p, pid_t pid, int status)
{
	static pid_t	prev_pid = 0;

	if (WIFEXITED(status))
		p->ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		p->ret = WTERMSIG(status) + 128;
		ft_ret_display_signal(pid, status, 0);
	}
	else if (WIFSTOPPED(status))
	{
		p->ret = WSTOPSIG(status) + 128;
		ft_ret_display_signal(pid, status, 1);
		p->child_pid = pid;
		if (prev_pid && prev_pid != p->child_pid)
		{
			kill(prev_pid, 2);
			prev_pid = p->child_pid;
		}
		else if (!prev_pid)
			prev_pid = p->child_pid;
	}
	return (p->ret);
}
