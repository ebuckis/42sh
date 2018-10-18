/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ac_init_slct.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 17:49:41 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 16:41:30 by kcabus      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "autocomp.h"

static void	fill_curr_dir(t_slct *root, t_navig *info)
{
	struct dirent	*dp;
	DIR				*dirp;

	if ((dirp = opendir("./")) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		}
		closedir(dirp);
	}
}

static void	fill_dir(t_slct *root, t_navig *info, char *line, char **table)
{
	struct dirent	*dp;
	DIR				*dirp;

	if (info->letters && !ft_strcmp(table[0], info->letters))
		ft_strdel(&info->letters);
	if (!line || (line && !ft_strchr(line, '/')))
		fill_curr_dir(root, info);
	else if ((dirp = opendir(line)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		}
		closedir(dirp);
	}
}

static char	**fill_pathes(void)
{
	char	**pathes;
	char	*str;

	str = NULL;
	if (!(str = getenv("PATH")))
		return (NULL);
	pathes = ft_strsplit(str, ':');
	return (pathes);
}

static void	free_init_slct(char **table, char **pathes)
{
	if (table)
		ft_free_tab(&table);
	if (pathes)
		ft_free_tab(&pathes);
}

t_slct		*init_slct(char *line, t_navig *info)
{
	t_slct	*root;
	char	**table;
	int		i;
	char	**pathes;

	i = 0;
	table = NULL;
	root = NULL;
	pathes = fill_pathes();
	if (info->s)
		table = ft_strsplit(info->s, ' ');
	if (!(root = root_slct()) || !line || !table)
		return (init_error(root, info, table, pathes));
	if (!(table[1]) && info->s && last_char(info->s) != ' ' &&
			last_char(info->s) != '/')
		fill_commands(root, info);
	else if (is_cmd(table[0], pathes) || last_char(info->s) == '/')
		fill_dir(root, info, line, table);
	free_init_slct(table, pathes);
	if (root->next != root)
		return (root);
	else
		return (free_slct(root, info));
}
