/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_heredoc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: yoginet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/06 13:00:36 by yoginet      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 13:00:38 by yoginet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/exec.h"

static int		delete_file(char **file)
{
	int		fd;
	int		pid;
	int		status;

	fd = 0;
	pid = 0;
	status = 0;
	if ((fd = open(file[1], O_RDONLY)) < 0)
		return (0);
	close(fd);
	if ((pid = fork()) < 0)
		return (1);
	if (pid == 0)
		execve("/bin/rm", file, NULL);
	else
		waitpid(pid, &status, 0);
	return (0);
}

int				delete_heredoc(char *file)
{
	char		**delete;
	int			ret;

	delete = NULL;
	ret = 0;
	if (file == NULL)
		return (1);
	if (!(delete = (char **)malloc(sizeof(char *) * 3)))
		return (1);
	delete[0] = ft_strdup("rm");
	delete[1] = ft_strdup(file);
	delete[2] = NULL;
	ret = delete_file(delete);
	ft_free_tab(&delete);
	return (ret);
}
