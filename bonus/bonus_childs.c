/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/05 23:15:07 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		exec_bonus(t_pipex *pipex, char *cmd, int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (exec_bonus)", 1);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error. (exec_bonus)", 1);
	/* if (close(pipex->fd[0]) == -1) */
	/* 	generic_err(pipex, "Close error. (exec_bonus)", 1); */
	pipex->cmd = ft_split(cmd, ' ');
	if (pipex->cmd == NULL)
		generic_err(pipex, "Malloc error. (exec_bonus -> ft_split)\n", 0);
	pipex->cmd_path = get_cmd(pipex, pipex->cmd[0]);
	if (pipex->cmd_path == NULL)
		generic_err(pipex, "Command does not exist. (exec_bonus -> get_cmd)\n", 0);
	if (execve(pipex->cmd_path, pipex->cmd, pipex->envp) == -1)
		generic_err(pipex, "Execve error. (exec_bonus)", 1);
	return (-1);
}
