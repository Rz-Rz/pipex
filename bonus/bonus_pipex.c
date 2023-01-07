/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/07 13:53:06 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <fcntl.h>
#include <unistd.h>

void	multipipe(char *cmd, t_pipex *pipex)
{
	int		pid;

	if (pipe(pipex->fd) == -1)
		generic_err(pipex, "Pipe error. (multipipe)", 1);
	pid = fork();
	if (pid == -1)
		generic_err(pipex, "Fork error. (multipipe)", 1);
	else if (pid == 0)
	{
		if (close(pipex->fd[0]) == -1)
			generic_err(pipex, "Close error. (multipipe)", 1);
		if (exec_bonus(pipex, cmd, STDIN_FILENO, pipex->fd[1]) == -1)
			generic_err(pipex, "Exec error. (multipipe)", 1);
	}
	else
	{
		if (close(pipex->fd[1]) == -1)
			generic_err(pipex, "Close error. (multipipe)", 1);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			generic_err(pipex, "Dup2 error. (multipipe)", 1);
		/* if (waitpid(pid, NULL, 0) == -1) */
		/* 	generic_err(pipex, "Waitpid error. (multipipe)", 1); */
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
	if (pipe(pipex.fd) == -1)
		generic_err(&pipex, "Pipe error.", 1);
	check_mode_infile(&pipex, &i);
	check_mode_outfile(&pipex);
	get_paths(&pipex, envp);
	while (i < argc - 2)
		multipipe(argv[i++], &pipex);
	exec_bonus(&pipex, argv[argc - 2], pipex.fd[0], pipex.fd_file2);
	return (0);
}

