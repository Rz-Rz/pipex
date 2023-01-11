/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 18:20:48 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	static const t_pipex	emptypipex;
	t_pipex					pipex;

	pipex = emptypipex;
	if (*envp == NULL)
		generic_err(&pipex, NULL, 0, EXIT_SUCCESS);
	if (argc != 5)
		generic_err(&pipex, "Wrong numbers of arguments.\n", 0, EXIT_SUCCESS);
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.fd_file1 = f_open(argv[1], O_RDONLY, 0);
	pipex.fd_file2 = f_open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	get_paths(&pipex, envp);
	if (pipe(pipex.fd) == -1)
		generic_err(&pipex, "Pipe error.\n", 1, EXIT_FAILURE);
	child_exec(&pipex);
	while (waitpid(0, NULL, 0) != -1)
		;
	close_fds(&pipex);
	free_pipex(&pipex);
	return (0);
}

void	child_exec(t_pipex *pipex)
{
	pipex->children1 = fork();
	if (pipex->children1 == -1)
		generic_err(pipex, "Fork error.\n", 1, EXIT_FAILURE);
	if (pipex->children1 == 0)
		exec(pipex, 2, pipex->fd_file1, pipex->fd[1]);
	close_fd(pipex, &pipex->fd[1], "Close error. (fd[1] in child_exec)");
	pipex->children2 = fork();
	if (pipex->children2 == -1)
		generic_err(pipex, "Fork error.\n", 1, EXIT_FAILURE);
	if (pipex->children2 == 0)
		exec(pipex, 3, pipex->fd[0], pipex->fd_file2);
	close_fd(pipex, &pipex->fd[0], "Close error. (fd[0] in child_exec)");
}
