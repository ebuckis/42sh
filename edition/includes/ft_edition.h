/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_edition.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 14:40:55 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 10:43:34 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_EDITION_H
# define FT_EDITION_H

# define KEY_CODE_DIR		(buf[0] == 27 && buf[1] == 91)
# define KEY_CODE_DELETE	(buf[2] == 51 && buf[3] == 126 && !buf[4])
# define KEY_CODE_UP		(buf[2] == 65 && !buf[3])
# define KEY_CODE_DOWN		(buf[2] == 66 && !buf[3])
# define KEY_CODE_RIGHT		(buf[2] == 67 && !buf[3])
# define KEY_CODE_LEFT		(buf[2] == 68 && !buf[3])
# define KEY_CODE_ENTER		(buf[0] == 10 && !buf[1])
# define KEY_CODE_TAB		(buf[0] == 9 && !buf[1])
# define KEY_CODE_ALT		(buf[0] == 27 && buf[1] == 27 && buf[2] == 91)
# define KEY_CODE_END		(buf[2] == 70 && !buf[3])
# define KEY_CODE_HOME		(buf[2] == 72)
# define KEY_CTRL_D			(buf[0] == 4 && !buf[1])
# define KEY_CODE_DEL		(buf[0] == 127 && !buf[1])
# define SIG_CTRLD			-4
# define EVENT_NO_FOUND		-3
# define IS_PRINTABLE		(buf[0] > 31 && buf[0] < 127 && !buf[1])
# define KEY_CTRL_U			(buf[0] == 21 && !buf[1])
# define KEY_CTRL_K			(buf[0] == 11 && !buf[1])
# define KEY_CTRL_E			(buf[0] == 5 && !buf[1])
# define KEY_CTRL_W			(buf[0] == 23 && !buf[1])
# define KEY_CTRL_T			(buf[0] == 20 && !buf[1])
# define HIST_FILE			".42sh_history"
# define RESET 				"\033[00m"

/*
** CTRL + U couper jusqu'au debut
** CTRL + K couper jusqu'a la fin
** CTRL + E copier jusqu'au debut
** CTRL + W copier jusqu'a la fin
** CTRL + T coller
*/

# define CHAR_AJOUT		1
# define CHAR_SUPPR		2
# define MOVE_RIGHT		3
# define MOVE_LEFT		4

# define CLOSE_HIST		-1
# define GET_HIST		1
# define SAVE_HIST		0
# define NEXT_HIST		1
# define PREV_HIST		-1

# define ID_NUM_NULL		-1
# define LAST_ID_NUM_NULL	-2
# define OCCURRENCE_NULL	-3
# define ID_NUM				1
# define LAST_ID_NUM		2
# define OCCURRENCE			3

# include "../../libft/includes/libft.h"
# include "../../parser/includes/ft_parser.h"
# include <curses.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <term.h>

typedef struct		s_navig
{
	struct termios	t;
	char			*s;
	char			*s_save;
	int				id_hist;
	char			*prompt;
	int				i;
	int				x;
	int				y;
	int				x_len;
	int				y_len;
	int				x_start;
	int				y_start;
	int				x_size;
	int				y_size;
	int				y_first;
	int				to_small;
	char			*tmp_char;
	int				err;
	int				tmp_int;
	int				statut;
	char			*letters;
	int				max_len;
	int				nb_elem;
	int				ac_x;
	int				ac_y;
	int				max_id;
	char			*pattern;
	char			*col;
}					t_navig;

typedef struct		s_hist
{
	char			*str;
	int				id;
	struct s_hist	*next;
	struct s_hist	*prev;
	int				current;
}					t_hist;

t_navig				g_nav;

char				*ft_edition(char *prompt, char *col);
int					ft_putcharint(int c);
int					ft_move_to_xy(int x, int y);
int					ft_get_size(int *x, int *y);
int					ft_init_nav(t_navig *n, char *p, char *col);
int					ft_init_term(struct termios *t);
int					ft_key_code(t_navig *n, char *buf);
int					ft_key_move(t_navig *n, char *buf);
void				ft_recup_pos(int *x, int *y);
void				ft_x_change(t_navig *n, int i);
struct termios		ft_default_edit(struct termios term);
int					ft_verif_term_size(t_navig *n);
int					ft_del_char(t_navig *n);
int					ft_maj_line(t_navig *n);
int					ft_new_char(t_navig *n, char *buf);
int					ft_maj_win(t_navig *n);
int					ft_key_alt(t_navig *n, char *buf);
int					ft_move_up(t_navig *n);
int					ft_push_enter(t_navig *n);
int					ft_copy_paste(t_navig *n, char *buf, int fr);
int					ft_maj_struct_nav(t_navig *n, char *str);
void				ft_put_prompt(char *deb, char *prompt);

char				*ft_get_hist_name(void);
int					ft_open_hist(void);
void				ft_file_to_list(void);
char				*ft_give_hist(int i, int id);
int					ft_add_hist(char *s, int boul, int value);
t_hist				*ft_close_hist(int i, t_hist *list);
void				ft_list_to_file(void);

int					ft_ring_the_bell(void);
void				ft_del_end_to_i(t_navig *n);
void				ft_signal_size(int s);
void				ft_delta_line(t_navig *n, int nb);
void				ft_goto_i_from_end(t_navig *n);
int					ft_no_new_name(t_navig *n, char *p);

int					ft_parse_excl(t_navig *n);
int					ft_ident_excl(char *s, int pos);
int					ft_is_interpreted(char *s, int pos);
int					ft_replace_line(t_navig *n, int *pos, int id);
int					ft_replace_s(char *s, t_navig *n, int pos);
void				ft_free_hist(t_hist **h);
void				ft_verif_histsize();

#endif
