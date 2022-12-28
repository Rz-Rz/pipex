/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:07:12 by kdhrif            #+#    #+#             */
/*   Updated: 2022/12/28 20:43:47 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	generic_err(t_pipex *pipex, char *str, int system)
{
	free_pipex(pipex);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[0]);
	if (system)
		perror(str);
	else
		write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	free_pipex(t_pipex *pipex)
{
	int i;

	i = 0;
	if (pipex->paths)
	{
		while (pipex->paths[i])
			free(pipex->paths[i++]);
		free(pipex->paths);
	}
	if (pipex->path)
		free(pipex->path);
	if (pipex->cmd1)
		free(pipex->cmd1);
	if (pipex->cmd2)
		free(pipex->cmd2);
	if (pipex->file1)
		free(pipex->file1);
	if (pipex->file2)
		free(pipex->file2);
}
