/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 09:07:05 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		exec(t_pipex *pipex, int arg, int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdin in exec)", 1);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (stdout in exec)", 1);
	close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in exec)");
	pipex->cmd = ft_split(pipex->argv[arg], ' ');
	if (pipex->cmd == NULL)
		generic_err(pipex, "Malloc error. (ft_split in exec)", 0);
	pipex->cmd_path = get_cmd(pipex, pipex->cmd[0]);
	if (pipex->cmd_path == NULL)
		generic_err(pipex, "Command does not exist. (get_cmd in exec)", 0);
	close_pipex(pipex);
	if (execve(pipex->cmd_path, pipex->cmd, pipex->envp) == -1)
		generic_err(pipex, "Execve error. (exec)", 1);
	return (-1);
}
