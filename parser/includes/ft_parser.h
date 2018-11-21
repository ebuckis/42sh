/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parser.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 08:57:09 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 14:09:50 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "../../libft/includes/libft.h"
# include "../../edition/includes/ft_edition.h"

# define SPACE			-1
# define WORD			'0'
# define SINGLE_QUOTE	'1'
# define DOUBLE_QUOTE	'2'
# define BACKSLASH		'3'
# define REDIR			'4'
# define HEREDOC		'5'
# define PIPE			'6'
# define AND			'7'
# define OR				'8'
# define SEMICOLON		'9'

typedef struct	s_parse
{
	char		*s;
	char		*str;
	char		*ident;
	char		**arg;
	char		**arg_id;
	int			len;
	int			err;
	int			i;
	int			j;
	int			k;
	int			ret;
	pid_t		child_pid;
	int			nb_hdoc;
	char		**hdoc;
	int			tmp_id;
}				t_parse;

typedef struct	s_doll
{
	char	*var;
	char	*key;
	char	*tmp;
	char	*arg;
	char	*p1;
	char	*p2;
	char	*p3;
}				t_doll;
/*
** s : line d'entree
** str : line parsee
** ident : meme format que str et permet d'identifier les arg
** arg : split de str
** arg_id : split de ident
*/
t_parse			*ft_parser(char *line, pid_t child_pid, int ret);
int				ft_antislash(t_parse *p);
t_parse			*ft_init_parse(char *line);
int				ft_is_separator(t_parse *p);
int				ft_is_white(char c);
int				ft_is_red(char c);
int				ft_parse_dquote(t_parse *p);
int				ft_parse_quote(t_parse *p);
int				ft_suite_line(t_parse *p, int i, char *prompt);
void			ft_end_while(t_parse *p, char c);
int				ft_separator(t_parse *p, int tmp);
int				ft_is_redirection(char c);
t_parse			**ft_save_struct(t_parse *parsing);
char			*ft_strjoin_free(char *line1, char *line2, int i, int j);
int				ft_or_and(t_parse *p);
int				ft_is_or_and(t_parse *p);
/*
** permet de garder une save de t_parse meme si on sort de la fonction
*/
int				ft_close_parse(void);
void			ft_free_tab(char ***t);
void			ft_free_tab3(char ***t);
/*
** ft_close permet de free la structure t_parse
*/
void			ft_add_space(t_parse *p);
void			ft_realloc_space(t_parse *p);
int				ft_heredoc(t_parse *p);

#endif
