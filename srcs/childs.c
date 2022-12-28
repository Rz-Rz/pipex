/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:29:33 by kdhrif            #+#    #+#             */
/*   Updated: 2022/12/28 21:22:57 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	exec(t_pipex *pipex, char *argv[], char *envp[], int arg)
{
	if (dup2(pipex->fd_file1, STDIN_FILENO) == -1)
		generic_err(pipex, "Dup2 error.\n", 1);
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		generic_err(pipex, "Dup2 error.\n", 1);
	if (close(pipex->fd[0]) == -1)
		generic_err(pipex, "Close error.\n", 1);
	pipex->cmd1 = ft_split(argv[arg], ' ');
	if (pipex->cmd1 == NULL)
		generic_err(pipex, "Malloc error. (ft_split)\n", 0);
	pipex->cmd1_path = get_cmd(pipex, pipex->cmd1[0]);
	if (pipex->cmd1_path == NULL)
		generic_err(pipex, "Command does not exist. (get_cmd)\n", 0);
	if (execve(pipex->cmd1_path, pipex->cmd1, envp) == -1)
		generic_err(pipex, "Execve error.\n", 1);
}
