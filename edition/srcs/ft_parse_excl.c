/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_excl.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 12:53:13 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 10:34:52 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_edition.h"

static int	ft_loop_cmp(char *s, int pos, int *i, char c)
{
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
		if ((s[i] == '\"' || s[i] == '\"') &&
			(ret = ft_loop_cmp(s, pos, &i, s[i])) != 0)
			return (ret);
		else if (s[i] == '\\' && s[i + 1])
		{
			if ((s[i + 1] == '\"' || s[i + 1] == '\"'))
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
	if (!c)
		return (ft_strdup(s));
	tmp[0] = (char)c;
	tmp[1] = '\0';
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
			if ((i == 0) || (s1[i - 1] != '\\'))
				break ;
		i++;
	}
	if (i != 0)
		str = ft_strsub(s1, 0, (size_t)i);
	ft_strdel(&s2);
	dprintf(2, "__fin de %s, str = : %s__\n", __func__, str);
	return (str);
}


int			ft_parse_excl(t_navig *n)
{
	int		ident;
	int		pos;
	int		cParse;
	int		check;

	check = 0;
	pos = 0;
	while ((pos = ft_strchr_index(n->s + pos, '!')) != -1)//voir le !!:
	{
		check = 1;
		dprintf(2, "__s : %s, pos : %d__\n", n->s, pos);
		if ((cParse = ft_is_interpreted(n->s, pos)) != -1 && (char)cParse != '\\')
		{
			dprintf(2, "__cParse : %d__\n", cParse);
			if ((ident = ft_ident_excl(n->s, pos)) < 0)
			{
				dprintf(2, "__ident : %d__\n", ident);
				return (0);//avec impression du message d'erreur
			}
			dprintf(2, "__ident : %d__\n", ident);
			n->pattern = ft_get_pattern(n->s + pos + 1, cParse);
			dprintf(2, "__pattern : %s__\n", n->pattern);
			if (ft_replace_line(n, &pos, ident) < 0)//modifier la valeur de pos (+= len du remplacement)
			{
				ft_maj_struct_nav(n, "");
				return (-1);
			}
		}
		ft_maj_struct_nav(n, ft_strdup(n->s));
		dprintf(2, "__pos : %d__\n", pos);
		dprintf(2, "__cParse : %d__\n", cParse);
	}
	if (check)
	{
		ft_putendl("");
		ft_putstr(n->s);
	}
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
	dprintf(2, "\n", );
*/

