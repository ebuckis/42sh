/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 14:21:33 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 12:47:02 by volivry     ###    #+. /#+    ###.fr     */
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
	free_tab(table);
	free_tab(pathes);
	return (NULL);
}
