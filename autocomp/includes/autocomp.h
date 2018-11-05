/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 15:32:40 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 15:57:55 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H

# include "../../libft/includes/libft.h"
# include "../../edition/includes/ft_edition.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <locale.h>
# include <dirent.h>

# define BLACK "\033[30m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define GREEN "\033[32m"
# define ORANGE "\033[38;5;208m"
# define L_BLUE "\033[38;5;51m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define RESET "\033[00m"

typedef struct			s_slct
{
	int					current;
	int					len;
	int					is_dir;
	int					is_exe;
	char				*name;
	int					index;
	int					x;
	int					y;
	struct s_slct		*next;
	struct s_slct		*prev;

}						t_slct;

t_slct					*g_slct;

void					ac_get_info(t_slct *slct, t_navig *info);
void					ac_add_after_lst(t_slct *elem, struct dirent *dp);
void					ac_add_before_lst(t_slct *elem, struct dirent *dp);
void					ac_add_queue(t_slct *root, struct dirent *dp);
void					ac_add_head(t_slct *root, struct dirent *dp);
void					ac_remove_elem(t_slct *elem);
t_slct					*root_slct(void);
t_slct					*init_slct(char **line, t_navig *info);
t_slct					*ac_first_elem(t_slct *root);
t_slct					*ac_last_elem(t_slct *root);
void					*free_slct(t_slct *lst, t_navig *info);
void					init_info(t_navig *info);
void					*init_error(t_slct *root, t_navig *info, char **table,
									char **pathes);
void					fill_commands(t_slct *root, t_navig *info);
void					ac_right_key(t_navig *info, t_slct *slct);
void					ac_left_key(t_navig *info, t_slct *slct);
void					ac_up_key(t_navig *info, t_slct *slct);
void					ac_down_key(t_navig *info, t_slct *slct);
void					ac_tab_key(t_navig *info, t_slct *slct);
int						key_input(t_navig *info, t_slct *slct, int *loop);
void					ac_print_arg(t_slct *slct, t_navig *info);
void					display(t_navig *info, t_slct *slct);
void					update_index(t_slct *root);
void					reset_screen(t_navig *info);
void					restore_curs(t_navig *info, t_slct *slct);
int						get_row_number(t_navig *info);
int						is_exe(char *name);
void					add_slct(t_slct *slct, t_navig *info);
void					erase_prev(t_navig *info);
int						slct_current(t_slct *slct, t_navig *info);
char					*get_last_word(char *line, t_navig *info);
int						contains_letters(char *name, char *letters);
int						is_cmd(char *cmd, char **pathes);
char					last_char(char *str);
t_list					*tab_to_lst(char **table);
void					*free_lst(t_list *lst);
int						ft_putchar_err(int c);
void					autocomp(t_navig *info);
char					*str_append(char *s1, char *s2);
void	   				change_tilde(char **str, t_navig *info);
void					add_bs_in_str(char **str);
int						add_bs(char *str);
void					free_init_slct(char **table, char **pathes, char **line);
int						ends_wo_space(char **table, char **pathes);

#endif
