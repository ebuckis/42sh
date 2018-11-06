/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 12:53:13 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 08:07:33 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int	ft_loop_cmp(char *s, int pos, int *i, char c)
{
	while (s[*i] && *i < pos)
	{
		if (s[*i] == "\\" && *i == pos - 1)
			return ((int)s[*i]);
		else if (s[*i] == "\\" && s[*i + 1] && s[*i + 1] == c)
			*i++;
		else if (s[*i] == c)
			return (0);
		*i++;
	}
	if (!s[*i])
		return (-1);
	return ((int)c);
}

int			ft_is_interpreted(char *s, int pos)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (s[i] && i < pos)
	{
		if ((s[i] == "\"" || s[i] == "\"") &&
			(ret = ft_loop_cmp(s, pos, &i, s[i])) != 0)
			return (ret);
		else if (s[i] == "\\" && s[i + 1])
		{
			if ((s[i + 1] == "\"" || s[i + 1] == "\""))
				i++;
			ret = (int)s[i];
		}
		else
			ret = 0;
		i++;
	}
	if (!s[i])
		return (-1);
	return (ret);
	//TODO: retourner si le '!' est interpreté ou non 

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

static int	ft_strchr_index(const char *s, char c)
{
	int i;

	i = 0;
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
	char	tmp[2];

	s = " \t|&;\n";//FIXME: voir tous les separateur
	tmp[0] = (char)c;
	tmp[1] = "\0";
	s = ft_strjoin(s, (const char *)tmp);
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
	while (s1[i])
	{
		if (ft_strchr(s2, s1[i]))
			if ((i == 0) || (s1[i - 1] != "\\"))
				break ;
		i++;
	}
	if (i != 0)
		str = ft_strsub(s1, 0, (size_t)i);
	ft_strdel(&s2);
	return (str);
}

int			ft_parse_excl(t_navig *n)
{
	int		ident;
	int		pos;
	int		cParse;

	pos = 0;
	while ((pos = ft_strchr_index(n->s + pos, '!') > 0))
	{
		if ((cParse = ft_is_interpreted(n->s, pos)) != -1 && cParse != "\\")
		{
			if ((ident = ft_ident_excl(n->s, pos)) < 0)
				return (0);//avec impression du message d'erreur
			n->pattern = ft_get_pattern(n->s + pos, cParse);
			ft_replace_line(n, &pos, ident, cParse);//modifier la valeur de pos (+= len du remplacement)
		}
	}
	ft_putstr(n->s);
	return (1);
}

/*
** TODO: remplir n->pattern
*/

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
*/

