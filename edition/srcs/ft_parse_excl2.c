/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl2.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 12:34:09 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 14:29:27 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int	ft_strchr_index(const char *s, int pos, char c)
{
	int i;

	i = pos;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_get_ending_char(char c)
{
	char	*s;
	char	*tmp;

	if (c == '\'')
		tmp = "\"";
	else if (c == '\"')
		tmp = "\'";
	else
		tmp = "\'\"";
	s = " \t|&;\n";
	s = ft_strjoin(s, tmp);
	return (s);
}

char		*ft_get_pattern(char *s1, int cparse)
{
	char	*s2;
	char	*str;
	int		i;

	str = NULL;
	s2 = ft_get_ending_char(cparse);
	i = 0;
	while (s1[i])
	{
		if (ft_strchr(s2, s1[i]))
			if ((i == 0) || (s1[i - 1] != '\\'))
				break ;
		i++;
	}
	if (i != 0)
		str = ft_strsub(s1, 0, (size_t)i);
	ft_strdel(&s2);
	return (str);
}

static void	check_ok(t_navig *n)
{
	ft_putendl("");
	ft_putstr(n->s);
}

int			ft_parse_excl(t_navig *n)
{
	int		ident;
	int		pos;
	int		cparse;
	int		check;

	check = 0;
	pos = 0;
	while ((pos = ft_strchr_index(n->s, pos, '!')) != -1)
	{
		check = 1;
		if ((cparse = ft_is_interpreted(n->s, pos)) != -1
				&& (char)cparse != '\\')
		{
			if ((ident = ft_ident_excl(n->s, pos)) < 0)
				return (EVENT_NO_FOUND);
			n->pattern = ft_get_pattern(n->s + pos + 1, cparse);
			if (ft_replace_line(n, &pos, ident) < 0)
				return (EVENT_NO_FOUND);
		}
		else
			pos++;
	}
	if (check)
		check_ok(n);
	return (1);
}
