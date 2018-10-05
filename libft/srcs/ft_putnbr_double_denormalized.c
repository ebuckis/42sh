/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_double_denormalized.c                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 11:37:39 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:45:55 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_char_double_denormalized2(char *res, int preci,
		t_field *cur, char *pow)
{
	char	*buf;

	ft_memdel((void**)&pow);
	buf = ft_round(res, preci);
	if (cur->type & G_MIN || cur->type & G_MAJ)
		ft_cut_end(buf);
	ft_memdel((void**)&res);
	return (buf);
}

char			*ft_char_double_denormalized(t_double *d, int preci,
		t_field *cur)
{
	char	*res;
	char	*buf;
	char	*sum;
	char	*pow;
	int		i;

	res = NULL;
	pow = ft_two_pow(d->e - 52);
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
	buf = ft_char_double_denormalized2(res, preci, cur, pow);
	return (buf);
}
