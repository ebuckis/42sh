/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 12:53:13 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 12:39:33 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int	ft_loop_cmp(char *s, int pos, int *i, char c)
{
	(*i)++;
	while (s[*i] && *i < pos)
	{
		if (s[*i] == '\\' && *i == pos - 1)
			return ((int)s[*i]);
		else if (s[*i] == '\\' && s[*i + 1] && s[*i + 1] == c)
			(*i)++;
		else if (s[*i] == c)
			return (0);
		(*i)++;
	}
	return ((int)c);
}

/*
** ft_loop_cmp :
** je boucle sur le char trouvé
** 1er	if		si j'ai un backslash avant le !
** 2eme	if		si j'ai un BS avant le char en question j'avance
** 3eme	if		si je suis su le char en question
*/

int			ft_is_interpreted(char *s, int pos)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (s[i] && i < pos)
	{
		if ((s[i] == '\'' || s[i] == '\"') && ret != '\\' &&
			(ret = ft_loop_cmp(s, pos, &i, s[i])) != 0)
		{
			return (ret);
		}
		else if (s[i] == '\\' && ret != '\\')
			ret = (int)s[i];
		else
			ret = 0;
		i++;
	}
	return (ret);
}

int			ft_ident_excl(char *s, int pos)
{
	if (ft_isdigit(s[pos + 1]))
		return (ID_NUM);
	else if (s[pos + 1] == '-')
	{
		if (s[pos + 2] && ft_isdigit(s[pos + 2]))
			return (LAST_ID_NUM);
		return (0);
	}
	else
		return (OCCURRENCE);
}
