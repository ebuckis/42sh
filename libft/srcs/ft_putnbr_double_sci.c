/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_double_sci.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/01 18:58:48 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 13:34:52 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_char_double_sci2(int *e, char *buf, int preci)
{
	*e += (buf[0] == '0') ? -1 : 1;
	buf[1] = (buf[0] == 0) ? buf[2] : '.';
	buf[2] = (buf[0] == 0) ? '.' : '0';
	buf[preci + 2] = 0;
}

static char		*ft_char_double_sci(t_double *d, t_field *cur)
{
	char	*res;
	char	*buf;
	int		e;
	char	*exp;

	buf = ft_two_pow(d->e - 53);
	e = ft_get_exponent(buf);
	ft_memdel((void**)&buf);
	if (d->e == -1023)
		buf = (e < 0) ? ft_char_double_denormalized(d, cur->preci - e + 1, cur)
			: ft_char_double_denormalized(d, cur->preci + 1, cur);
	else
		buf = (e < 0) ? ft_char_double(d, cur->preci - e + 1, cur) :
			ft_char_double(d, cur->preci + 1, cur);
	e = ft_get_exponent(buf);
	res = ft_char_dec_to_sci(buf, cur->preci + 1, e);
	buf = ft_round(res, cur->preci);
	if (buf[0] == '0' || buf[2] == '.')
		ft_char_double_sci2(&e, buf, cur->preci);
	exp = ft_char_exp_double(e, cur);
	ft_memdel((void**)&res);
	res = ft_strjoin(buf, exp);
	ft_memdel((void**)&buf);
	ft_memdel((void**)&exp);
	return (res);
}

static int		ft_putnbr_double_sci2(t_field *cur)
{
	int		ret;
	char	*exp;

	ret = 0;
	ret += ft_putnbr_size(0);
	ret += (cur->preci) ? ft_putchar_size('.') : 0;
	ret += (cur->preci) ? ft_putchar_sizel('0', cur->preci) : 0;
	exp = ft_char_exp_double(0, cur);
	ret += ft_putstr_size(exp);
	ft_memdel((void**)&exp);
	return (ret);
}

int				ft_putnbr_double_sci(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 1024 && d->m == 0)
		ret += (cur->type & E_MAJ || cur->type & G_MAJ) ? ft_putstr_size("INF")
			: ft_putstr_size("inf");
	else if (d->e == 1024)
		ret += (cur->type & E_MAJ || cur->type & G_MAJ) ? ft_putstr_size("NAN")
			: ft_putstr_size("nan");
	else if (d->e == -1023 && d->m == 0)
		ret += ft_putnbr_double_sci2(cur);
	else
	{
		buf = ft_char_double_sci(d, cur);
		ret += ft_putstr_size(buf);
		ft_memdel((void**)&buf);
	}
	return (ret);
}

int				ft_doublelen_sci(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 1024)
		ret = 3;
	else if (d->e == -1023 && d->m == 0)
		ret = (cur->preci) ? cur->preci + 6 : 5;
	else
	{
		buf = ft_char_double_sci(d, cur);
		ret += ft_strlen(buf);
		ft_memdel((void**)&buf);
	}
	return (ret);
}
