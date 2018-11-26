/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 14:21:33 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:41:55 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

void	fill_commands(t_slct *root, t_navig *info)
{
	struct dirent	*dp;
	DIR				*dirp;
	char			**pathes;
	char			*str;
	int				i;

	i = 0;
	str = NULL;
	dp = NULL;
	str = getenv("PATH");
	pathes = ft_strsplit(str, ':');
	while (pathes[i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
				if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
					ac_add_queue(root, dp);
			closedir(dirp);
		}
		ft_strdel(&pathes[i]);
		i++;
	}
	free(pathes);
}

int		is_cmd(char *cmd, char **pathes)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	i = -1;
	while (pathes[++i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
				if (!ft_strcmp(dp->d_name, cmd))
				{
					while (pathes[i])
						ft_strdel(&pathes[i++]);
					closedir(dirp);
					return (1);
				}
			closedir(dirp);
		}
	}
	return (0);
}

void	*init_error(t_slct *root, t_navig *info, char **table, char **pathes)
{
	free_slct(root, info);
	ft_free_tab(&table);
	ft_free_tab(&pathes);
	return (NULL);
}

void	free_init_slct(char **table, char **pathes, char **line)
{
	ft_strdel(line);
	if (table)
		ft_free_tab(&table);
	if (pathes)
		ft_free_tab(&pathes);
}

int		ends_wo_space(char **table, char **pathes)
{
	int	i;

	i = 0;
	while (table[i + 1])
		i++;
	if (i && (last_char(table[i - 1]) == '|' || last_char(table[i - 1]) == ';'
		|| last_char(table[i - 1]) == '&' || !is_cmd(table[i - 1], pathes))
		&& !ft_strchr(table[i], '/'))
		if (table[i - 1][0] != '-')
			return (1);
	return (0);
}
