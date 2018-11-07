/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   change_tilde.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 16:30:27 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/07 16:06:01 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"
#include <sys/types.h>
#include <pwd.h>

static char	*get_user(void)
{
	uid_t			uid;
	char			*name;
	struct passwd	*pw;

	uid = getuid();
	pw = getpwuid(uid);//FIXME: voir si autorisée
	name = ft_strdup(pw->pw_name);
	return (name);
}

void		remove_end(char **str)
{
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	*str = str_append(*str, "/");
	len = ft_strlen(*str) - 1;
	tmp = ft_strnew(len);
	while ((*str)[len - 1] != '/')
		len--;
	while (i < len)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void		change_tilde(char **str, t_navig *info)
{
	char	*usr;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 1;
	usr = get_user();
	tmp = ft_strdup("/Users/");
	tmp = str_append(tmp, usr);
	ft_strdel(&usr);
	tmp2 = ft_strnew(ft_strlen(*str) - 1);
	while ((*str)[i])
	{
		tmp2[i - 1] = (*str)[i];
		i++;
	}
	tmp2 = str_append(tmp2, info->letters);
	ft_strdel(str);
	tmp = str_append(tmp, tmp2);
	remove_end(&tmp);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}
