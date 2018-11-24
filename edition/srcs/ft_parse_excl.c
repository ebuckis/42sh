/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 12:53:13 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 14:04:51 by kcabus      ###    #+. /#+    ###.fr     */
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
//	if (!s[*i])
//		return (-1);
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

	//dprintf(2, "///////////////////debut de |%s|***\n", __func__);
	ret = 0;
	i = 0;
	while (s[i] && i < pos)
	{
		if ((s[i] == '\'' || s[i] == '\"') && ret != '\\' &&
			(ret = ft_loop_cmp(s, pos, &i, s[i])) != 0)
			{
			//dprintf(2, "/////////////////// ret avec une sortie de is interpreted = |%d|***\n", ret);
			return (ret);
			}
		else if (s[i] == '\\' && ret != '\\')
			ret = (int)s[i];
		else
			ret = 0;
		//dprintf(2, "/////////////////// ret fi de while = |%d|***\n", ret);
		i++;
	}
//	if (!s[i])
//		return (-1);
	//dprintf(2, "/////////////////// ret en FIN de  is_interpreted = |%d|***\n", ret);
	return (ret);

	/*
	** parcourir la string depuis zéro,
	** si on recontre un 
	**
	**
	**
	**
	*/
}

int			ft_ident_excl(char *s, int pos)
{
	if (ft_isdigit(s[pos + 1]))
		return (ID_NUM);
	else if (s[pos + 1] == '-')
	{
		if (s[pos + 2] && ft_isdigit(s[pos+ 2]))
			return (LAST_ID_NUM);
		return (0);
	}
	else
		return (OCCURRENCE);
}

static int	ft_strchr_index(const char *s, int pos, char c)
{
	int i;

		//dprintf(2, "__dans : %s, s : %s__\n", __func__, s);
	i = pos;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
		//dprintf(2, "__Fin normal: %s__ avec i = %d__\n", __func__, i);
			return (i);
		}
		i++;
	}
		//dprintf(2, "__Fin error: %s__\n", __func__);
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
	s = " \t|&;\n";//FIXME: voir tous les separateur
	s = ft_strjoin(s, tmp);
	return (s);
}

char		*ft_get_pattern(char *s1, int cParse)
{
	char	*s2;
	char	*str;
	int		i;

	str = NULL;
	s2 = ft_get_ending_char(cParse);
	i = 0;
	//dprintf(2, "___________s1 |%s| s2|%s| cParse|%c|_____________\n", s1, s2, (char)cParse);
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
	//dprintf(2, "__fin de %s, str = : %s__\n", __func__, str);
	return (str);
}


int			ft_parse_excl(t_navig *n)
{
	int		ident;
	int		pos;
	int		cParse;
	int		check;
//	char	*str;

	check = 0;
	pos = 0;
	while ((pos = ft_strchr_index(n->s, pos, '!')) != -1)//TODO: voir le !!:
	{
		check = 1;
		if ((cParse = ft_is_interpreted(n->s, pos)) != -1 && (char)cParse != '\\')
		{
			if ((ident = ft_ident_excl(n->s, pos)) < 0)
				return (EVENT_NO_FOUND);
			n->pattern = ft_get_pattern(n->s + pos + 1, cParse);
			if (ft_replace_line(n, &pos, ident) < 0)
				return (EVENT_NO_FOUND);
		}
		else
			pos++;
//		str = ft_strdup(n->s);
//		ft_strdel(&str);
	}
	if (check)
	{
		ft_putendl("");
		ft_putstr(n->s);
	}
	return (1);
}

/*
** a gérer :
** ![char]		->derniere occurence, si pas trouvée "42sh: event not found: %s"
** ![int]		->boucle jusqu'au bon id, sinon "42sh: %s: event not found"
** !-[int]		->va chercher en arriere , error idem
**
** ident prend different val:
** OCCURRENCE
** OCCURRENCE_NULL
** ID_NUM
** ID_NUM_NULL
** LAST_ID_NUM
** LAST_ID_NUM_NULL
	//dprintf(2, "\n", );
*/

