/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   infos_hist.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kcabus <kcabus@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 13:36:13 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 13:52:32 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

/*
** set les 3 variables locales pour l'historique au lancement de 42sh
*/

char		**init_var_history(void)
{
	char	**env_loc;

	if ((env_loc = (char**)malloc(sizeof(char*) * 4)))
	{
		env_loc[0] = strdup("HISTSIZE=500");
		env_loc[1] = strdup("HISTFILE=500");
		env_loc[2] = strdup("HISTFILESIZE=500");
		env_loc[3] = NULL;
	}
	return (env_loc);
}

/*
**	Return HISTSIZE
*/

int			info_histsize(void)
{
	int		h;
	char	*value_txt;
	char	***p_env;

	p_env = ft_save_p_env(NULL);
	value_txt = get_value(p_env, "HISTSIZE", 1, 1);
	h = (value_txt) ? ft_atoi(value_txt) : 500;
	h = (h < 0) ? 0 : h;
	ft_memdel((void**)&value_txt);
	return (h);
}

/*
**	Return HISTFILE
*/

int			info_histfile(void)
{
	int		h;
	char	*value_txt;
	char	***p_env;

	p_env = ft_save_p_env(NULL);
	value_txt = get_value(p_env, "HISTFILE", 1, 1);
	h = (value_txt) ? ft_atoi(value_txt) : 500;
	h = (h < 0) ? 0 : h;
	ft_memdel((void**)&value_txt);
	return (h);
}

/*
**	Return HISTFILESIZE
*/

int			info_histfilesize(void)
{
	int		h;
	char	*value_txt;
	char	***p_env;

	p_env = ft_save_p_env(NULL);
	value_txt = get_value(p_env, "HISTFILESIZE", 1, 1);
	h = (value_txt) ? ft_atoi(value_txt) : 500;
	h = (h < 0) ? 0 : h;
	ft_memdel((void**)&value_txt);
	return (h);
}
