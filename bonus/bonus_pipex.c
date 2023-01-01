/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/01 21:14:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	static const t_pipex EmptyPipex;
	t_pipex pipex;

	pipex = EmptyPipex;
	if (argc != 5)
		generic_err(&pipex, "Wrong numbers of arguments.\n", 0);
	pipex.fd_file1 = f_open(argv[1], O_RDONLY, 0);
	pipex.fd_file2 = f_open(argv[4], O_RDWR | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(pipex.fd) == -1)
		generic_err(&pipex, "Pipe error.\n", 1);
	get_paths(&pipex, envp);
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
		exec(pipex, 2, pipex->fd_file1, pipex->fd[1]);
	close(pipex->fd[1]);
	pipex->children2 = fork();
	if (pipex->children2 == -1)
		generic_err(pipex, "Fork error.\n", 1);
	if (pipex->children2 == 0)
		exec(pipex, 3, pipex->fd[0], pipex->fd_file2);
}




