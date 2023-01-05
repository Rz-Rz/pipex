/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 22:33:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/05 23:36:19 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <unistd.h>

void   check_mode_infile(t_pipex *pipex, int *i)
{
	if (ft_strncmp("here_doc", pipex->argv[1], 8) == 0)
	{
		if (pipex->argc < 6)
			generic_err(pipex, "Wrong numbers of arguments. (check_mode_infile)", 0);
		here_doc(pipex);
		pipex->heredoc = 1;
		*i = 3;
	}
	else
	{
		pipex->fd_file1 = f_open(pipex->argv[1], O_RDONLY, 0);
		*i = 2;
		if (dup2(pipex->fd_file1, 0) == -1)
			generic_err(pipex, "Dup2 error. (check_mode_infile)", 1);
	}
}

void	check_mode_outfile(t_pipex *pipex)
{
	if (pipex->heredoc == 1)
		pipex->fd_file2 = f_open(pipex->argv[pipex->argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		pipex->fd_file2 = f_open(pipex->argv[pipex->argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

void   here_doc(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
		generic_err(pipex, "Pipe error. (here_doc)", 1);
	pipex->pid = fork();
	if (pipex->pid == -1)
		generic_err(pipex, "Fork error. (here_doc)", 1);
	if (pipex->pid == 0)
		put_heredoc(pipex);
	else {
		if (close(pipex->fd[1]) == -1)
			generic_err(pipex, "Close error. (here_doc)", 1);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			generic_err(pipex, "Dup2 error. (here_doc)", 1);
		/* wait(NULL); */
	}
}

void	put_heredoc(t_pipex *pipex)
{
	char	*line;

	close(pipex->fd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			generic_err(pipex, "Get next line failed. (put_heredoc)", 0);
		if (ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])) == 0)
			break ;
		ft_putstr_fd(line, pipex->fd[1]);
		free(line);
	}
	free(line);
	close(pipex->fd[1]);
}
