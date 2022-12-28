/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:28:22 by kdhrif            #+#    #+#             */
/*   Updated: 2022/12/28 21:40:12 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	static const t_pipex EmptyPipex;
	t_pipex pipex;

	pipex = EmptyPipex;
	/* if (argc != 5) */
	/* 	generic_err(&pipex, "Wrong numbers of arguments.\n", 0); */
	pipex.fd_file1 = f_open(argv[1], O_RDONLY, 0);
	/* pipex.fd_file2 = f_open(argv[4], O_RDWR | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); */
	if (pipe(pipex.fd) == -1)
		generic_err(&pipex, "Pipe error.\n", 1);
	get_paths(&pipex, envp);
	pipex.children1 = fork();
	if (pipex.children1 == -1)
		generic_err(&pipex, "Fork error.\n", 1);
	if (pipex.children1 == 0)
		exec(&pipex, argv, envp, 2);
	waitpid(pipex.children1, NULL, 0);
	free_pipex(&pipex);
	close(pipex.fd_file1);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	/* close(pipex.fd_file2); */
	return (0);
}

