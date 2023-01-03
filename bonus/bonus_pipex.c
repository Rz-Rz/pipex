/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/03 11:55:54 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <fcntl.h>
#include <unistd.h>

void	multipipe(char *cmd, t_pipex *pipex)
{
	int		pid;
	int		status;

	if (pipe(pipex->fd) == -1)
		generic_err(pipex, "Pipe error.\n", 1);
	pid = fork();
	if (pid == -1)
		generic_err(pipex, "Fork error.\n", 1);
	else if (pid == 0)
	{
		close(pipex->fd[0]);
		if (exec_bonus(pipex, cmd, pipex->fd[0], pipex->fd[1]) == -1)
			generic_err(pipex, "Exec error.\n", 1);
	}
	else
	{
		if (close(pipex->fd[0]) == -1)
			generic_err(pipex, "Close error.\n", 1);
		if (waitpid(pid, &status, 0) == -1)
			generic_err(pipex, "Waitpid error.\n", 1);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	static const t_pipex EmptyPipex;
	t_pipex pipex;

	pipex = EmptyPipex;
	/* if (argc != 5) */
	/* 	generic_err(&pipex, "Wrong numbers of arguments.\n", 0); */
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	check_mode_infile(&pipex);
	check_mode_outfile(&pipex);
	get_paths(&pipex, envp);

	while (i < argc - 2)
		multipipe(argv[i++], &pipex);
	if (pipe(pipex.fd) == -1)
		generic_err(&pipex, "Pipe error.\n", 1);
	child_exec(&pipex);
	waitpid(pipex.children1, NULL, 0);
	waitpid(pipex.children2, NULL, 0);
	close_fd(&pipex);
	free_pipex(&pipex);
	return (0);
}

void	child_exec(t_pipex *pipex)
{
	pipex->children1 = fork();
	if (pipex->children1 == -1)
		generic_err(pipex, "Fork error.\n", 1);
	if (pipex->children1 == 0)
		exec(pipex, 3, pipex->fd_file1, pipex->fd[1]);
	close(pipex->fd[1]);
	pipex->children2 = fork();
	if (pipex->children2 == -1)
		generic_err(pipex, "Fork error.\n", 1);
	if (pipex->children2 == 0)
		exec(pipex, 4, pipex->fd[0], pipex->fd_file2);
}




