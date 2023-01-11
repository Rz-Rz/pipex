/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:07:12 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 16:10:50 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	generic_err(t_pipex *pipex, char *str, int system, int exitcode)
{
	char	*s;

	if (system == 1)
		perror(str);
	else if (system == 2)
	{
		s = ft_strjoin(str, ": Command not found\n");
		ft_putstr_fd(s, STDERR_FILENO);
		free(s);
	}
	else if (system == 3)
	{
		s = ft_strjoin(str, ": No such file or directory\n");
		ft_putstr_fd(s, STDERR_FILENO);
		free(s);
	}
	else
		write(2, str, ft_strlen(str));
	free_pipex(pipex);
	close_pipex(pipex);
	exit(exitcode);
}

void	close_pipex(t_pipex *pipex)
{
	if ((pipex->fd_file1 > 2))
		close_fd(pipex, &pipex->fd_file1, "Close error. \
				(fd_file1 in close_pipex)");
	if (pipex->fd_file2 > 2)
		close_fd(pipex, &pipex->fd_file2, "Close error. \
				(fd_file2 in close_pipex)");
	if (pipex->fd[0] > 2)
		close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in close_pipex)");
	if (pipex->fd[1] > 2)
		close_fd(pipex, &pipex->fd[1], "Close error. (fd[1] in close_pipex)");
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->paths)
	{
		while (pipex->paths[i])
			free(pipex->paths[i++]);
		free(pipex->paths);
	}
	if (pipex->path)
		free(pipex->path);
	i = 0;
	if (pipex->cmd)
	{
		while (pipex->cmd[i])
			free(pipex->cmd[i++]);
		free(pipex->cmd);
	}
	if (pipex->cmd_path)
		free(pipex->cmd_path);
}
