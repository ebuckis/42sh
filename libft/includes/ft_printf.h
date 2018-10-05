/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/08 11:03:59 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 14:35:42 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <locale.h>
# include <float.h>
# include <inttypes.h>

# define FLAG		"#0-+ $'brk"
# define WIDTH		"123456789*"
# define CONV		"hljzL"
# define TYPE		"sSpdDioOuUxXcCeEfFgGn%"

# define SHARP		0x1
# define ZERO		0x2
# define MINUS		0x4
# define PLUS		0x8
# define SPACE		0x10
# define ASTERIX	0x20
# define DOLLAR		0x40
# define APOSTROPHE	0x80
# define B_FLAG		0x100
# define R_FLAG		0x200
# define K_FLAG		0x400

# define HH_FLAG	0x1
# define H_FLAG		0x2
# define L_FLAG		0x4
# define LL_FLAG	0x8
# define J_FLAG		0x10
# define Z_FLAG		0x20
# define L_MAJ		0x40

# define PERCENT	0x1
# define C_MIN		0x2
# define C_MAJ		0x4
# define S_MIN		0x8
# define S_MAJ		0x10
# define D_MIN		0x20
# define D_MAJ		0x40
# define U_MIN		0x80
# define U_MAJ		0x100
# define O_MIN		0x200
# define O_MAJ		0x400
# define X_MIN		0x800
# define X_MAJ		0x1000
# define POINTER	0x2000
# define E_MIN		0x4000
# define E_MAJ		0x8000
# define F_MIN		0x10000
# define F_MAJ		0x20000
# define G_MIN		0x40000
# define G_MAJ		0x80000
# define N_FLAG		0x100000

typedef struct		s_field
{
	int				text;
	int				flag;
	int				width;
	int				width_ast;
	int				preci;
	int				preci_ast;
	int				conv;
	int				type;
	int				len;
	int				nb;
	int				ret;
	int				l;
	int				spc_bfr;
	int				spc_aft;
	int				zero;
	int				plus;
	int				minus;
	int				pos;
	long int		pos_long;
	char			letter;
	int				error;
	struct s_field	*next;
}					t_field;

typedef struct		s_double
{
	int				s;
	int				e;
	long int		m;
}					t_double;

t_field				*ft_parse(const char *str, va_list *va);
t_field				*ft_flags(t_field *cur, const char *str, int i);
t_field				*ft_width(t_field *cur, const char *str, int i,
		va_list *va);
t_field				*ft_preci(t_field *cur, const char *str, int i,
		va_list *va);
t_field				*ft_sizem(t_field *cur, const char *str, int i);
t_field				*ft_type(t_field *cur, const char *str, int i,
		va_list *va);
int					ft_printf(const char *format, ...);
int					ft_printf_type(t_field *cur, va_list *va, int *ret);
void				ft_printf_percent(t_field *cur);
void				ft_printf_c(t_field *cur, va_list *va);
void				ft_printf_cc(t_field *cur, va_list *va);
void				ft_printf_z(t_field *cur);
void				ft_printf_s(t_field *cur, va_list *va);
void				ft_printf_ss(t_field *cur, va_list *va);
void				ft_printf_hd(t_field *cur, va_list *va);
void				ft_printf_hhd(t_field *cur, va_list *va);
void				ft_printf_d(t_field *cur, va_list *va);
void				ft_printf_ld(t_field *cur, va_list *va);
void				ft_printf_lld(t_field *cur, va_list *va);
void				ft_printf_jd(t_field *cur, va_list *va);
void				ft_printf_zd(t_field *cur, va_list *va);
void				ft_printf_d_flag(t_field *cur);
void				ft_printf_d_space(t_field *cur);
void				ft_printf_hhu(t_field *cur, va_list *va);
void				ft_printf_hu(t_field *cur, va_list *va);
void				ft_printf_u(t_field *cur, va_list *va);
void				ft_printf_lu(t_field *cur, va_list *va);
void				ft_printf_llu(t_field *cur, va_list *va);
void				ft_printf_ju(t_field *cur, va_list *va);
void				ft_printf_zu(t_field *cur, va_list *va);
void				ft_printf_u_flag_space(t_field *cur);
void				ft_printf_hho(t_field *cur, va_list *va);
void				ft_printf_ho(t_field *cur, va_list *va);
void				ft_printf_o(t_field *cur, va_list *va);
void				ft_printf_lo(t_field *cur, va_list *va);
void				ft_printf_llo(t_field *cur, va_list *va);
void				ft_printf_jo(t_field *cur, va_list *va);
void				ft_printf_zo(t_field *cur, va_list *va);
void				ft_printf_o_flag_space(t_field *cur);
void				ft_printf_hhx(t_field *cur, va_list *va);
void				ft_printf_hx(t_field *cur, va_list *va);
void				ft_printf_x(t_field *cur, va_list *va);
void				ft_printf_lx(t_field *cur, va_list *va);
void				ft_printf_llx(t_field *cur, va_list *va);
void				ft_printf_jx(t_field *cur, va_list *va);
void				ft_printf_zx(t_field *cur, va_list *va);
void				ft_printf_x_flag(t_field *cur);
void				ft_printf_x_zero(t_field *cur);
void				ft_printf_p(t_field *cur, va_list *va);
void				ft_printf_e(t_field *cur, va_list *va);
void				ft_printf_e2(t_field *cur, t_double *d);
void				ft_printf_le(t_field *cur, va_list *va);
void				ft_printf_le2(t_field *cur, t_double *d);
void				ft_printf_f(t_field *cur, va_list *va);
void				ft_printf_f2(t_double *d, t_field *cur);
void				ft_printf_lf(t_field *cur, va_list *va);
void				ft_printf_lf2(t_double *d, t_field *cur);
void				ft_printf_g(t_field *cur, va_list *va);
void				ft_printf_lg(t_field *cur, va_list *va);
void				ft_printf_a(t_field *cur, va_list *va);
void				ft_printf_aa(t_field *cur, va_list *va);
void				ft_printf_hhn(va_list *va, int *ret);
void				ft_printf_hn(va_list *va, int *ret);
void				ft_printf_n(va_list *va, int *ret);
void				ft_printf_ln(va_list *va, int *ret);
void				ft_printf_lln(va_list *va, int *ret);
void				ft_printf_jn(va_list *va, int *ret);
void				ft_printf_zn(va_list *va, int *ret);
int					ft_putwchar(wchar_t c);
int					ft_wcharlen(wchar_t c);
int					ft_putstr_size(char *str);
int					ft_putstr_sizel(char *str, int i);
int					ft_putchar_size(int c);
int					ft_putchar_sizel(char c, int i);
int					ft_putwstr(wchar_t *wstr);
int					ft_putwstr_singlel(wchar_t *wstr, int l);
int					ft_putwstrl(wchar_t *wstr, int l);
int					ft_wstrlen(wchar_t *wc);
int					ft_wstrlen_single(wchar_t *wstr);
int					ft_wstrlenl(wchar_t *wc, int l);
int					ft_putnbr_size(int n);
int					ft_putnbr_long_size(long int n);
int					ft_putnbr_u_size(unsigned int n);
int					ft_putnbr_u_long_size(unsigned long int n);
int					ft_putnbr_base(unsigned int n, unsigned int base, int maj);
int					ft_putnbr_long_base(unsigned long n, unsigned long base,
		int maj);
int					ft_putnbr_double(t_double *d, t_field *cur);
int					ft_putnbr_double_sci(t_double *d, t_field *cur);
int					ft_putnbr_longdouble_sci(t_double *d, t_field *cur);
int					ft_putnbr_longdouble(t_double *d, t_field *cur);
int					ft_doublelen(t_double *d, t_field *cur);
int					ft_longdoublelen(t_double *d, t_field *cur);
int					ft_doublelen_sci(t_double *d, t_field *cur);
int					ft_longdoublelen_sci(t_double *d, t_field *cur);
t_double			*ft_double_info(double d);
t_double			*ft_longdouble_info(long double d);
char				*ft_char_double(t_double *d, int preci, t_field *cur);
char				*ft_char_double_denormalized(t_double *d, int preci,
		t_field *cur);
char				*ft_char_longdouble(t_double *d, int preci, t_field *cur);
int					ft_get_exponent(char *res);
char				*ft_char_dec_to_sci(char *dec, int preci, int e);
char				*ft_char_exp_double(int e, t_field *cur);
int					ft_nbr_size(int n);
int					ft_nbr_long_size(long int n);
int					ft_nbr_u_size(unsigned int n);
int					ft_nbr_u_long_size(unsigned long int n);
int					ft_nbr_size_base(unsigned int n, unsigned int base);
int					ft_nbr_long_size_base(unsigned long int n,
		unsigned long int base);
char				*ft_two_pow(int pow);
char				*ft_two_pow_minus(int pow);
char				*ft_sum(char *s1, char *s2, int end);
char				*ft_sum_integer(char *s1, char *s2);
char				*ft_sum_fraction(char *s1, char *s2);
char				*ft_sum_mixt(char *s1_int, char *s1_frac, char *s2_int,
		char *s2_frac);
int					ft_inf_one(char *s);
int					ft_dot(char *s);
char				*ft_integer(char *s);
char				*ft_fraction(char *s);
char				*ft_round(char *s, int preci);
void				ft_cut_end(char *s);

#endif
