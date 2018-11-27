/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_bin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 14:24:58 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 14:55:21 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

/*
**  recupere les differents chemin de la variable PATH de l'env
*/

static char	**ft_path(char **env)
{
	int		i;
	char	*path;
	char	**tab_bin;

	i = -1;
	while (env[++i])
	{
		if ((path = ft_strstr(env[i], "PATH=")))
		{
			path += 5;
			tab_bin = ft_strsplit(path, ':');
			return (tab_bin);
		}
	}
	return (NULL);
}

/*
** on check si le binaire existe avec stat
*/

char		*check_bin3(char *bin, int warning)
{
	struct stat buf;
	int			ret;

	if ((ret = stat(bin, &buf)) == 0)
		return (ft_strdup(bin));
	else
	{
		if (warning)
			ft_putendl_fd_arg("42sh: no such file or directory: ", bin);
	}
	return (NULL);
}

/*
** cas ou on check si le binaire est present dans les dossiers
** de la var PATH de l'env
*/

char		*check_bin2(char *tab0, char **env)
{
	char		*tmp;
	char		**tab_path;
	int			i;
	char		*bin;
	char		*bin2;

	bin = tab0;
	tab_path = ft_path(env);
	i = -1;
	while (tab_path && tab_path[++i])
	{
		tmp = ft_strjoin(tab_path[i], "/");
		bin = ft_strjoin(tmp, tab0);
		ft_memdel((void**)&tmp);
		if ((bin2 = check_bin3(bin, 0)))
		{
			ft_free_tab(&tab_path);
			ft_memdel((void**)&bin);
			return (bin2);
		}
		ft_memdel((void**)&bin);
	}
	ft_putendl_fd_arg("42sh: command not found: ", tab0);
	ft_free_tab(&tab_path);
	return (NULL);
}

/*
** check_bin : verif si le 1er arg de tab_commande est un binaire du path
** on check si chemin absolu du binaire si commence par / ou ./
*/

char		*check_bin(char **tab_com, char **env)
{
	if (tab_com)
	{
		if (tab_com[0][0] == '/' || (tab_com[0][0] == '.' &&
					tab_com[0][1] == '/'))
			return (check_bin3(tab_com[0], 1));
		else
			return (check_bin2(tab_com[0], env));
	}
	return (NULL);
}
