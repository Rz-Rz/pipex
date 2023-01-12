/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/12 10:47:39 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdlib.h>

int	exec(t_pipex *pipex, int arg, int in, int out)
{
	if (in == -1)
		generic_err(pipex, NULL, 0, EXIT_FAILURE);
	if (out == -1)
		generic_err(pipex, NULL, 0, EXIT_FAILURE);
	if (dup2(in, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (in in exec)", 1, EXIT_FAILURE);
	if (dup2(out, STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (out in exec)", 1, EXIT_FAILURE);
	close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in exec)");
	pipex->cmd = ft_split(pipex->argv[arg], ' ');
	if (pipex->cmd == NULL)
		generic_err(pipex, "Malloc error. (ft_split in exec)", 0, EXIT_FAILURE);
	pipex->cmd_path = get_cmd(pipex, pipex->cmd[0]);
	if (pipex->cmd_path == NULL)
		generic_err(pipex, pipex->argv[arg], 2, CMD_NOT_FOUND);
	close_pipex(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, pipex->envp) == -1)
		generic_err(pipex, "Execve error. (exec)", 1, EXIT_FAILURE);
	return (-1);
}
