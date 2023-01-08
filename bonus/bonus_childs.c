/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:46:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	exec_bonus(t_pipex *pipex, char *cmd, int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdin exec_bonus)", 1);
	if (dup2(out, STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdout exec_bonus)", 1);
	pipex->cmd = ft_split(cmd, ' ');
	if (pipex->cmd == NULL)
		generic_err(pipex, "Malloc error. (exec_bonus -> ft_split)\n", 0);
	pipex->cmd_path = get_cmd(pipex, pipex->cmd[0]);
	if (pipex->cmd_path == NULL)
		generic_err(pipex, cmd, 2);
	close_pipex(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, pipex->envp) == -1)
		generic_err(pipex, "Execve error. (exec_bonus)", 1);
	return (-1);
}
