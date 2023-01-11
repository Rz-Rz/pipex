/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:07:12 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 16:11:05 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

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
		if (close(pipex->fd_file1) == -1)
			perror("close (fd_file1)");
	if (pipex->fd_file2 > 2)
		if (close(pipex->fd_file2) == -1)
			perror("close (fd_file2)");
	if (pipex->fd[0] > 2)
		if (close(pipex->fd[0]) == -1)
			perror("close (fd[0])");
	if (pipex->fd[1] > 2)
		if (close(pipex->fd[1]) == -1)
			perror("close (fd[1])");
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
