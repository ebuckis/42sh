/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_longdouble_sci.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/05 15:36:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:40:30 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_char_exp_longdouble(int e, t_field *cur)
{
	char	*exp;
	int		l;
	char	*buf;

	l = (e * e >= 100 * 100) ? 5 : 4;
	l += (e * e >= 1000 * 1000) ? 1 : 0;
	exp = ft_strnew(l);
	exp[0] = (cur->type & E_MAJ && cur->type & G_MAJ) ? 'E' : 'e';
	exp[1] = (e < 0) ? '-' : '+';
	buf = (e >= 0) ? ft_itoa(e) : ft_itoa(-e);
	if (e * e >= 10 * 10)
		ft_strcpy(&exp[2], buf);
	else
	{
		exp[2] = '0';
		ft_strcpy(&exp[3], buf);
	}
	exp[3] = (e == 0) ? '0' : exp[3];
	ft_memdel((void**)&buf);
	return (exp);
}

static void		ft_char_longdouble_sci2(char *buf, char *exp)
{
	ft_memdel((void**)&buf);
	ft_memdel((void**)&exp);
}

static char		*ft_char_longdouble_sci(t_double *d, t_field *cur)
{
	char	*res;
	char	*buf;
	int		e;
	char	*exp;

	buf = ft_two_pow(d->e - 63);
	e = ft_get_exponent(buf);
	ft_memdel((void**)&buf);
	buf = (e < 0) ? ft_char_longdouble(d, cur->preci - e + 1, cur) :
		ft_char_longdouble(d, cur->preci + 1, cur);
	e = ft_get_exponent(buf);
	res = ft_char_dec_to_sci(buf, cur->preci + 1, e);
	buf = ft_round(res, cur->preci);
	if (buf[0] == '0' || buf[2] == '.')
	{
		e += (buf[0] == '0') ? -1 : 1;
		buf[1] = (buf[0] == 0) ? buf[2] : '.';
		buf[2] = (buf[0] == 0) ? '.' : '0';
		buf[cur->preci + 2] = 0;
	}
	exp = ft_char_exp_longdouble(e, cur);
	ft_memdel((void**)&res);
	res = ft_strjoin(buf, exp);
	ft_char_longdouble_sci2(buf, exp);
	return (res);
}

int				ft_putnbr_longdouble_sci(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 16385 && d->m == 0)
		return ((cur->type & E_MAJ || cur->type & G_MAJ) ? ft_putstr_size("INF")
			: ft_putstr_size("inf"));
	else if (d->e == 16385)
		return ((cur->type & E_MAJ || cur->type & G_MAJ) ? ft_putstr_size("NAN")
			: ft_putstr_size("nan"));
	else if (d->e == -16384 && d->m == 0)
	{
		ret += ft_putnbr_size(0);
		ret += (cur->preci) ? ft_putchar_size('.') : 0;
		ret += (cur->preci) ? ft_putchar_sizel('0', cur->preci) : 0;
		buf = ft_char_exp_longdouble(0, cur);
	}
	else
		buf = ft_char_longdouble_sci(d, cur);
	ret += ft_putstr_size(buf);
	ft_memdel((void**)&buf);
	return (ret);
}

int				ft_longdoublelen_sci(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 16385)
		ret = 3;
	else if (d->e == -16384 && d->m == 0)
		ret = (cur->preci) ? cur->preci + 6 : 5;
	else
	{
		buf = ft_char_longdouble_sci(d, cur);
		ret += ft_strlen(buf);
		ft_memdel((void**)&buf);
	}
	return (ret);
}
