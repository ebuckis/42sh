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
			if (dp->d_name[0] != '.' && last_char(info->s) == ' ')
				ac_add_queue(root, dp);
			else if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		}
		closedir(dirp);
	}
}

static void	fill_dir(t_slct *root, t_navig *info, char **line, char **table)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				i;
	char			*tmp;

	i = 0;
	tmp = NULL;
	tmp = ft_strdup(*line);
	while (table[i + 1])
		i++;
	if (info->letters && i && !ft_strcmp(table[i - 1], info->letters))
		ft_strdel(&info->letters);
	if ((*line)[0] == '~' && (*line)[1] == '/')
		change_tilde(&tmp, info);
	if (!table[i] || (table[i] && !ft_strchr(table[i], '/'))
	|| last_char(info->s) == ' ')
		fill_curr_dir(root, info);
	else if ((dirp = opendir(tmp)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if (dp->d_name[0] != '.' &&
					contains_letters(dp->d_name, info->letters))
				ac_add_queue(root, dp);
		}
		closedir(dirp);
	}
	ft_strdel(&tmp);
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

static int	ends_wo_space(char **table, char **pathes)
{
	int	i;

	i = 0;
	while (table[i + 1])
		i++;
	if (i && (last_char(table[i - 1]) == '|' || last_char(table[i - 1]) == ';'
		|| last_char(table[i - 1]) == '&' || !is_cmd(table[i - 1], pathes))
		&& !ft_strchr(table[i], '/'))
		return (1);
	return (0);
}

t_slct		*init_slct(char **line, t_navig *info)
{
	t_slct	*root;
	char	**table;
	char	**pathes;

	table = NULL;
	root = NULL;
	pathes = fill_pathes();
	if (info->s)
		table = ft_strsplit(info->s, ' ');
	if (!(root = root_slct()) || !line || !table)
		return (init_error(root, info, table, pathes));
	if (!table[1] && last_char(info->s) != ' ' && !ft_strchr(info->s, '/'))
		fill_commands(root, info);
	else if (!table[1] && last_char(info->s) != ' ' && ft_strchr(info->s, '/'))
		fill_dir(root, info, line, table);
	else if (last_char(info->s) == ' ')
			fill_dir(root, info, line, table);
	else
		(ends_wo_space(table, pathes)) == 1 ? fill_commands(root, info) :
			fill_dir(root, info, line, table);
	ft_strdel(line);
	free_init_slct(table, pathes);
	if (root->next != root)
		return (root);
	else
		return (free_slct(root, info));
}
