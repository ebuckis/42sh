/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 15:06:26 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 09:41:35 by bpajot      ###    #+. /#+    ###.fr     */
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
** gestion valeur retour exit que si pas pipe
*/

static void		ft_exit(int *a, char *arg)
{
	int		i;

	i = 0;
	while (arg && ((i == 0 && arg[i] == '-') || ft_isdigit(arg[i])))
		i++;
	if (arg && !arg[i])
		*a = (unsigned char)ft_atoi(arg);
	else if (!arg)
		*a = 0;
	else
	{
		ft_printf("21sh: exit: %s: numeric argument required\n", arg);
		ft_putstr_fd("21sh: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*a = 255;
	}
	ft_printf("exit\n");
}

/*
** gestion exit ou ; en boucle + tilde et dollar
*/

static void		ft_manage_semicolon_exit(t_parse *p, int *a, char ***p_env)
{
	int		i;
	int		n;
	int		begin;

	n = 0;
	i = 0;
	while (p->arg_id[i])
	{
		if (ft_strequ(p->arg[i], "exit") && (!p->arg[i + 1] ||
			p->arg_id[i + 1][0] < PIPE))
			break ;
		begin = i;
		while (p->arg_id[i] && !ft_strchr(p->arg_id[i], SEMICOLON))
			i++;
		i += (p->arg_id[i]) ? 1 : 0;
		n++;
		ft_tilde_dollar(p, begin, p_env);
		ft_manage_pipe(p, begin, p_env);
	}
	if (p->arg_id[i] && ft_strequ(p->arg[i], "exit"))
		ft_exit(a, p->arg[i + 1]);
}

/*
** affichage auteurs via manage_signal
** affichage titre 21sh
** en boucle, edition, parsing puis execution
*/

static void		main2(char *string, char ***p_env, int *a, int debug)
{
	static int		ret = 0;
	static int		child_pid = 0;
	t_parse			*p;

	if (string)
	{
		if ((p = ft_parser(string, child_pid, ret)))
		{
			if (debug)
				debug_display_struct(p);
			ft_manage_semicolon_exit(p, a, p_env);
			ret = p->ret;
			child_pid = p->child_pid;
		}
		ft_memdel((void**)&string);
		ft_close_parse();
	}
}

int				main(int argc, char *argv[], char *env[])
{
	char	*string;
	int		a;
	int		begin;
	char	**my_env;

	if (!isatty(0))
		return (0);
	manage_signal();
	my_env = ft_getenv(argc, argv, env);
	a = -1;
	begin = 0;
	while (a == -1)
	{
		string = (!begin++) ? ft_strdup("toilet -f bigascii12  21 sh | lolcat")
			: ft_edition("21sh $> ");
		if (argc == 2 && ft_strstr(argv[1], "debug"))
			main2(string, &my_env, &a, 1);
		else
			main2(string, &my_env, &a, 0);
	}
	ft_free_tab(&my_env);
	return (a);
}
