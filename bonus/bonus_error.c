/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:07:12 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/05 22:11:48 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void 	unlink_err(t_pipex *pipex, char *str, int system, char *target)
{
	unlink(target);
	generic_err(pipex, str, system);
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
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
}
