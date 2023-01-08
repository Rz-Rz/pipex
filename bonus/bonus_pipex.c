/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 19:58:27 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	multipipe(char *cmd, t_pipex *pipex, int i)
{
	int		pid;

	if (pipe(pipex->fd) == -1)
		generic_err(pipex, "Pipe error. (multipipe)", 1);
	pid = fork();
	if (pid == -1)
		generic_err(pipex, "Fork error. (multipipe)", 1);
	if (i == pipex->argc - 2 && pid == 0)
	{
		close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in multipipe)");
		if (exec_bonus(pipex, cmd, STDIN_FILENO, pipex->fd_file2) == -1)
			generic_err(pipex, "Exec error. (multipipe)", 1);
		waitpid(pid, &pipex->status, 0);
	}
	else if (pid == 0)
	{
		close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in multipipe)");
		if (exec_bonus(pipex, cmd, STDIN_FILENO, pipex->fd[1]) == -1)
			generic_err(pipex, "Exec error. (multipipe)", 1);
	}
	else
	{
		close_fd(pipex, &pipex->fd[1], "Close error. (fd[1] in multipipe)");
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			generic_err(pipex, "Dup2 error. (multipipe)", 1);
		close_fd(pipex, &pipex->fd[0], "Close error. (fd[1] in multipipe)");
	}
}

int main(int argc, char *argv[], char *envp[])
{
	static const t_pipex	EmptyPipex;
	t_pipex					pipex;
	int						i;

	pipex = EmptyPipex;
	if (*envp == NULL)
		generic_err(&pipex, "No environment. (main)", 0);
	if (argc < 5)
		generic_err(&pipex, "Wrong numbers of arguments.", 0);
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	check_mode_infile(&pipex, &i);
	check_mode_outfile(&pipex);
	get_paths(&pipex, envp);
	while (i <= argc - 2)
	{
		multipipe(argv[i], &pipex, i);
		i++;
	}
	while(waitpid(0, NULL, 0) != -1)
		;
	success(&pipex);
	return (0);
}
