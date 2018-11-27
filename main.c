/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 15:06:26 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 13:30:34 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./exec/includes/exec.h"

/*
** transforme les *char en *wchar_t et remplace les -1 non imprimables par le
** caractere speciale '·' pour l'afficghae du debug
*/

static void		debug_display_struct(t_parse *p)
{
	int		i;
	wchar_t *str;
	wchar_t *ident;

	ft_printf("----------\n");
	ft_printf("p->s :\t\t%s\n", p->s);
	str = ft_strdup_wchar(p->str);
	ident = ft_strdup_wchar(p->ident);
	ft_printf("p->str:\t\t%S\n", str);
	ft_printf("p->ident:\t%S\n", ident);
	i = -1;
	while (p->arg[++i])
	{
		ft_printf("arg[%d]:\t\t%s\n", i, p->arg[i]);
		ft_printf("arg_id[%d]:\t%s\n", i, p->arg_id[i]);
	}
	ft_printf("----------\n");
	ft_memdel((void**)&str);
	ft_memdel((void**)&ident);
}

/*
** gestion exit ou ; en boucle + tilde et dollar
*/

static void		ft_manage_semicolon_exit(t_parse *p, char ***p_env)
{
	int		i;
	int		n;
	int		begin;

	n = 0;
	i = 0;
	while (p->arg_id[i])
	{
		begin = i;
		while (p->arg_id[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
			i++;
		i += (p->arg_id[i]) ? 1 : 0;
		n++;
		ft_manage_and_or(p, begin, p_env);
	}
}

/*
** affichage auteurs via manage_signal
** affichage titre 21sh
** en boucle, edition, parsing puis execution
*/

static int		main2(char *string, char ***p_env, int debug, int ret)
{
	static int		child_pid = 0;
	t_parse			*p;

	if (string)
	{
		if ((p = ft_parser(string, child_pid, ret)))
		{
			if (debug)
				debug_display_struct(p);
			ft_manage_semicolon_exit(p, p_env);
			ret = p->ret;
			child_pid = p->child_pid;
		}
		ft_memdel((void**)&string);
		ft_close_parse();
	}
	return (ret);
}

/*
** affichage ascii art au demarrage
** puis prompt turquoise si retour commande = 0 , sinon prompt rouge
** my_env[0] = listing variables d'environnement recupere au lancement de 42sh
** my_env[1] = listing variables locales (vide au demarrage)
*/

int				main(int argc, char *argv[], char *env[])
{
	char			*string;
	int				begin;
	char			***my_env;
	static int		ret = 0;

	if (!isatty(0))
		return (0);
	manage_signal();
	my_env = ft_getenv(argc, argv, env);
	begin = 0;
	if (!(ft_open_hist()))
		return (0);
	while (101)
	{
		if (!begin++)
			string = ft_strdup("toilet -f bigascii12  42 sh | lolcat\
			; setenv CLICOLOR 1");
		else
			string = ft_edition((ret) ? "\033[31m42sh $> \033[00m" :
				"\033[36m42sh $> \033[00m");
		dprintf(2, "------------%s\n", string);//TODO: a rm
		if (argc == 2 && ft_strstr(argv[1], "debug"))
			ret = main2(string, my_env, 1, ret);
		else
			ret = main2(string, my_env, 0, ret);
	}
	return (0);
}
