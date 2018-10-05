/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_signal.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 17:29:56 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 09:56:17 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
** ft_signal_ctrl_c ignore le Ctrl-C pour le 21sh mais pas pour ces fils
** a faire, si edition en cours, return string NULL et p->ret = 1
** voir si on passe ret en static pour avoir un echo $? coherant
*/

static void		ft_go_to_end(t_navig *n)
{
	n->x = n->x_len;
	n->y = n->y_len;
	n->i = ft_strlen(n->s);
	ft_move_to_xy(n->x, n->y);
}

static void		ft_signal_ctrl_c(int s)
{
	(void)s;
	if (g_nav.statut)
		ft_go_to_end(&g_nav);
	ft_putendl("");
	if (g_nav.statut)
	{
		ft_strdel(&(g_nav.s));
		ft_strdel(&(g_nav.s_save));
		ft_init_nav(&g_nav, g_nav.prompt);
	}
}

/*
** ft_signal_stop ignore le Ctrl-Z pour le 21sh mais pas pour ces fils
*/

static void		ft_signal_stop(int s)
{
	(void)s;
	if (g_nav.statut)
	{
		ft_putendl("");
		ft_strdel(&(g_nav.s));
		ft_strdel(&(g_nav.s_save));
		ft_init_nav(&g_nav, "21sh $> ");
	}
}

/*
** manage_signal :
** affiche les auterus au debut du main
** ignore certains signaux et intercepte Ctrl-C et Ctrl-Z
*/

void			manage_signal(void)
{
	setlocale(LC_ALL, "");
	ft_printf("%C kcabus\n%C bpajot\n", L'©', L'©');
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGTSTP, ft_signal_stop);
	signal(SIGCONT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGURG, SIG_IGN);
}
