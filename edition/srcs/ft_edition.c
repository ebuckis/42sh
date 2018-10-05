/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_edition.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 16:17:54 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 11:58:00 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static char	*ft_ctrl_d(t_navig *n)
{
	ft_strdel(&(n->s));
	n->s = ft_strdup("exit");
	if (!(n->err = ft_push_enter(n)))
		return (NULL);
	n->err = SIG_CTRLD;
	n->statut = 0;
	return (n->s);
}

/*
** free la current line
** et envoie exit au programme
** avec un code d'erreur approprié
*/

static int	ft_whilesuite(t_navig *n, char *buf)
{
	if (KEY_CODE_DIR || KEY_CODE_DEL || KEY_CODE_ALT || IS_PRINTABLE)
	{
		if (!(ft_key_code(n, buf)))
			return (0);
	}
	else
		ft_copy_paste(n, buf, 0);
	return (1);
}

/*
** fait appel aux fonctions associees aux fleches
** ou aux 'sigaux' de copie/coller
*/

char		*ft_lance_edit(t_navig *n)
{
	char		buf[5];

	ft_x_change(n, MOVE_RIGHT);
	while (1)
	{
		while (ft_verif_term_size(n) < 0)
			if (!(n->err = ft_maj_win(n)))
				return (NULL);
		ft_bzero(buf, 5);
		read(0, buf, 4);
		if (buf[0] == 10 && !buf[1])
		{
			n->err = ft_push_enter(n);
			break ;
		}
		else if (KEY_CTRL_D && !ft_strlen(n->s))
			return (ft_ctrl_d(n));
		else if (!(n->err = ft_whilesuite(n, buf)))
			return (NULL);
	}
	if (n->err < 1)
		return (NULL);
	ft_strdel(&(n->s_save));
	n->statut = 0;
	return (n->s);
}

/*
** while principal
** on verifie si la taille du terminal est valide
** par rapport a la taille de la ligne
** -> sinon on boucle 'resize me'
** on lit sur l'entree standard et on effectue
** les actions suvant les touches recues
*/

char		*ft_edition(char *prompt)
{
	char		*str;

	str = NULL;
	if (!(g_nav.err = ft_init_term(&(g_nav.t))))
		return (NULL);
	if (!(g_nav.err = ft_init_nav(&g_nav, prompt)))
		return (NULL);
	signal(SIGWINCH, ft_signal_size);
	str = ft_lance_edit(&g_nav);
	g_nav.t = ft_default_edit(g_nav.t);
	return (str);
}

/*
** initialisation du terminal
** intialistation de la structure de navigation
** remise en mode 'normal' du terminal
*/
