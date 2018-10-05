/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 08:39:05 by kcabus       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/26 15:21:54 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	**ft_read_fichier(char *buf, char **s)
{
	if (!*s)
		*s = ft_strdup(buf);
	else
		*s = ft_strjoin_del(*s, buf);
	return (s);
}

static int	ft_strchr_index(const char *s, int c)
{
	int i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		else
			i++;
	}
	return (-1);
}

static int	ft_copy_s(char **s, char **line)
{
	int		i;

	i = ft_strchr_index(*s, '\n');
	if (i == -1)
		i = ft_strlen(*s);
	*line = ft_strsub(*s, 0, i);
	if (ft_strlen(*s) == 0)
	{
		ft_strdel(s);
		return (0);
	}
	*s = ft_strsub_del(*s, i + 1, (ft_strlen(*s) - (i + 1)));
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			n;
	char		buf[BUFF_SIZE + 1];
	static char *s = NULL;

	if ((n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		s = *ft_read_fichier(buf, &s);
		if (ft_strchr_index(s, '\n') == -1)
			return (get_next_line(fd, line));
	}
	if (n == -1)
		return (-1);
	buf[0] = '\0';
	s = *ft_read_fichier(buf, &s);
	return (ft_copy_s(&s, line));
}
