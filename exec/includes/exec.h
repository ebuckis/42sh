/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 13:45:17 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/03 13:03:34 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../parser/includes/ft_parser.h"
# include "../../libft/includes/libft.h"
# include "../../autocomp/includes/autocomp.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <locale.h>

typedef struct	s_opt_h
{
	int			c;
	int			d;
	int			a;
	int			n;
	int			r;
	int			w;
	int			p;
	int			s;
	int			print_line;
	int			offset;
	char		*filename;
}				t_opt_h;

void			ft_manage_pipe(t_parse *p, int begin, char ***p_env);
void			ft_fork_shell(t_parse *p, int *tab_pipe, char ***p_env,
		int nb_pipe);
char			**manage_redir(t_parse *p, int begin, char ***p_env, int off);
void			ft_redir(t_parse *p, int redir_lim[2], char **env,
		int nb_redirec);
int				check_builtin(char **tab_com);
int				check_builtin2(char **tab_com);
void			run_builtin_free(t_parse *p, char **tab_com, char ***p_env,
		int tab_pipe_i);
void			run_builtin_exit(t_parse *p, char **tab_com, char ***p_env,
		int tab_pipe_i);
void			run_builtin(t_parse *p, char **tab_com, char ***p_env,
		int tab_pipe_i);
char			*check_bin(char **tab_pipe_i, char **env);
void			ft_execve(t_parse *p, int tab_pipe_i, char ***p_env);
int				ft_check_all_exec(t_parse *p, int *tab_pipe, char ***p_env);
char			***ft_getenv(int argc, char **argv, char **env);
char			*ft_home(char **env);
char			*ft_getpwd(char **env, int old);
void			ft_setpwd(char **env, int old, char *pwd);
int				ft_cd(char **arg, char ***p_env);
void			usage_cd(char *str);
char			*ret_target(char **arg, int l, int p, int q);
int				ft_echo(char **arg);
int				ft_env(t_parse *p, char **arg, char **env, int tab_pipe_i);
int				ft_fg(t_parse *p);
int				display_env(char **env);
char			**ft_mix_env(char **env, char **env2);
int				ft_doublon(char *line, char **arg, int j);
int				ft_tab_size(char **arg, char **tab_ref);
int				ft_tab_size2(char **arg);
int				ft_setenv(char **arg, char ***env);
int				ft_unsetenv(char **arg, char ***env);
void			manage_signal(void);
int				ft_ret_display(t_parse *p, pid_t pid, int status);
int				ft_redir_out(t_parse *p, int *i, char **env);
int				ft_redir_in(t_parse *p, int *i, char **env);
char			*get_path_redir(t_parse *p, int *i, char **env);
int				ft_putendl_fd_arg(char *str, char *path);
void			ft_manage_and_or(t_parse *p, int begin, char ***p_env);
int				delete_heredoc(char *file);
int				ft_exit(char **arg, char ***p_env);

int				ft_len_tab(char **tabl);
int				info_histsize(void);
int				info_histfile(void);
int				info_histfilesize(void);
/*
**delete
*/
int				delete_history(void);
int				delete_line_history(int id);
/*
**history
*/
int				ft_print_history_len(int nb, int i, int histsize);
int				ft_history(char **arg, char ***p_env);
/*
**history struct
*/
int				history_del_pos(int pos);
int				search_options(t_opt_h **h, char **arg);
t_opt_h			*check_hist(char **arg);
t_opt_h			*delete_struct_hist(t_opt_h *h);
/*
**ft_err_hist
*/
int				history_usage(void);
int				history_out(int id);
int				history_out_str(char *str);
int				history_invalid(char *str, int i);
int				history_arg(char *str);

int				histo_suite(t_opt_h *h, char **arg);
t_parse			*ft_dollar(t_parse *p, int i, int *j, char ***p_env);
t_parse			*ft_tilde_dollar(t_parse *p, int i, char ***p_env);
int				ft_equal(t_parse *p, char **arg, char ***env, int tab_pipe_i);
int				ft_set(char ***p_env);
int				ft_unset(char **arg, char ***p_env);
int				ft_doublon3(char *line, char **arg);
char			**ft_unsetenv2(char **arg, char **env, int nb_double);
int				ft_export(char **arg, char ***p_env);
char			*get_value(char ***p_env, char *key, int start, int end);
int				histo_p(t_opt_h *h, char **arg);
int				histo_s(t_opt_h *h, char **arg);
char			***ft_save_p_env(char ***p_env);
char			**init_var_history(void);

#endif
