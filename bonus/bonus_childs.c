/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 18:41:02 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <stdlib.h>

int	exec_bonus(t_pipex *pipex, char *cmd, int in, int out)
{
	if (in == -1)
		generic_err(pipex, NULL, 0, EXIT_FAILURE);
	if (dup2(in, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdin exec_bonus)", 1, EXIT_FAILURE);
	if (dup2(out, STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdout exec_bonus)", 1, EXIT_FAILURE);
	pipex->cmd = ft_split(cmd, ' ');
	if (pipex->cmd == NULL)
		generic_err(pipex, "Malloc error. (exec_bonus -> ft_split)\n"\
				, 0, EXIT_FAILURE);
	pipex->cmd_path = get_cmd(pipex, pipex->cmd[0]);
	if (pipex->cmd_path == NULL)
		generic_err(pipex, cmd, 2, CMD_NOT_FOUND);
	close_pipex(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, pipex->envp) == -1)
		generic_err(pipex, "Execve error. (exec_bonus)", 1, EXIT_FAILURE);
	return (-1);
}
