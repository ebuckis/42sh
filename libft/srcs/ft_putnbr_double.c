/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_double.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/20 09:56:11 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:46:28 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

t_double		*ft_double_info(double d)
{
	unsigned long int	*ptr;
	t_double			*d_info;

	if ((d_info = (t_double*)malloc(sizeof(t_double))) == NULL)
		return (NULL);
	ptr = (unsigned long int*)&d;
	d_info->s = *ptr >> 63;
	d_info->e = (*ptr & 0x7ff0000000000000) >> 52;
	d_info->e -= 1023;
	d_info->m = *ptr & 0x000fffffffffffff;
	return (d_info);
}

static char		*ft_char_double2(char *res, char *pow, int preci, t_field *cur)
{
	char	*buf;

	buf = ft_sum(res, pow, 0);
	ft_memdel((void**)&res);
	res = ft_sum(buf, pow, 0);
	ft_memdel((void**)&buf);
	ft_memdel((void**)&pow);
	buf = ft_round(res, preci);
	if (cur->type & G_MIN || cur->type & G_MAJ)
		ft_cut_end(buf);
	ft_memdel((void**)&res);
	return (buf);
}

char			*ft_char_double(t_double *d, int preci, t_field *cur)
{
	char	*res;
	char	*buf;
	char	*sum;
	char	*pow;
	int		i;

	res = NULL;
	pow = ft_two_pow(d->e - 53);
	i = -1;
	while (++i < 52)
	{
		buf = ft_sum(pow, pow, 0);
		ft_memdel((void**)&pow);
		if ((d->m >> i) % 2)
		{
			sum = ft_sum(res, buf, 0);
			ft_memdel((void**)&res);
			res = ft_strdup(sum);
			ft_memdel((void**)&sum);
		}
		pow = ft_strdup(buf);
		ft_memdel((void**)&buf);
	}
	buf = ft_char_double2(res, pow, preci, cur);
	return (buf);
}

int				ft_putnbr_double(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 1024 && d->m == 0)
		ret += (cur->type & F_MAJ || cur->type & G_MAJ) ? ft_putstr_size("INF")
			: ft_putstr_size("inf");
	else if (d->e == 1024)
		ret += (cur->type & F_MAJ || cur->type & G_MAJ) ? ft_putstr_size("NAN")
			: ft_putstr_size("nan");
	else if (d->e == -1023 && d->m == 0)
	{
		ret += ft_putnbr_size(0);
		ret += (cur->preci && !(cur->type & G_MIN) && !(cur->type & G_MAJ)) ?
			ft_putchar_size('.') + ft_putchar_sizel('0', cur->preci) : 0;
	}
	else
	{
		buf = (d->e == -1023) ? ft_char_double_denormalized(d, cur->preci, cur)
			: ft_char_double(d, cur->preci, cur);
		ret += ft_putstr_size(buf);
		ft_memdel((void**)&buf);
	}
	return (ret);
}

int				ft_doublelen(t_double *d, t_field *cur)
{
	int		ret;
	char	*buf;

	ret = 0;
	if (d->e == 1024)
		ret = 3;
	else if (d->e == -1023 && d->m == 0)
		ret = (cur->preci && !(cur->type & G_MIN) && !(cur->type & G_MAJ))
			? cur->preci + 2 : 1;
	else
	{
		buf = (d->e == -1023) ? ft_char_double_denormalized(d, cur->preci, cur)
			: ft_char_double(d, cur->preci, cur);
		ret += ft_strlen(buf);
		ft_memdel((void**)&buf);
	}
	return (ret);
}
