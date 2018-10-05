/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_double_sci2.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/05 17:41:42 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:39:23 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_char_exp_double(int e, t_field *cur)
{
	char	*exp;
	int		l;

	l = (e * e >= 100 * 100) ? 5 : 4;
	exp = ft_strnew(l);
	exp[0] = (cur->type & E_MAJ || cur->type & G_MAJ) ? 'E' : 'e';
	exp[1] = (e < 0) ? '-' : '+';
	if (e >= 0)
	{
		exp[2] = (e >= 100) ? e / 100 + '0' : e / 10 + '0';
		exp[3] = (e >= 100) ? e % 100 / 10 + '0' : e % 10 + '0';
		exp[4] = (e >= 100) ? e % 10 + '0' : 0;
	}
	else
	{
		exp[2] = (e <= -100) ? -e / 100 + '0' : -e / 10 + '0';
		exp[3] = (e <= -100) ? -e % 100 / 10 + '0' : -e % 10 + '0';
		exp[4] = (e <= -100) ? -e % 10 + '0' : 0;
	}
	return (exp);
}

int				ft_get_exponent(char *res)
{
	int		i;
	int		exp;

	i = 0;
	while (res[i] == '0' || res[i] == '.')
	{
		if (res[i] == '.')
		{
			exp = -1;
			while (res[++i] == '0')
				exp--;
			return ((res[i] && res[i] != '0') ? exp : 0);
		}
		i++;
	}
	exp = 0;
	while (res[i] && res[i] != '.')
	{
		i++;
		exp += (res[i] && res[i] != '.') ? 1 : 0;
	}
	return (exp);
}

static void		ft_char_dec_to_sci2(char *dec, int preci, char *sci)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dec[i] == '0' || dec[i] == '.')
		i++;
	sci[0] = dec[i];
	sci[1] = (preci) ? '.' : 0;
	while (j < preci)
	{
		sci[2 + j] = dec[1 + i + j];
		j++;
	}
}

char			*ft_char_dec_to_sci(char *dec, int preci, int e)
{
	char	*sci;
	int		i;
	int		dot;

	i = 0;
	dot = 0;
	sci = (preci == 0) ? ft_strnew(1) : ft_strnew(2 + preci);
	if (e >= 0)
	{
		sci[0] = dec[0];
		if (preci > 0)
		{
			sci[1] = '.';
			while (i < preci)
			{
				dot += (dec[1 + i] == '.' && !dot) ? 1 : 0;
				sci[2 + i] = dec[1 + i + dot];
				i++;
			}
		}
	}
	else
		ft_char_dec_to_sci2(dec, preci, sci);
	ft_memdel((void**)&dec);
	return (sci);
}
