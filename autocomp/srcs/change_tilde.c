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
#include <pwd.h>

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
	usr = getenv("HOME");
	if (!usr)
		return ;
	tmp = ft_strdup(usr);
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
