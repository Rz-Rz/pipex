/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 22:33:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/02 19:34:55 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <unistd.h>

void   check_mode_infile(t_pipex *pipex)
{
	if (ft_strncmp("here_doc", pipex->argv[1], 8) == 0)
	{
		here_doc(pipex);
		pipex->heredoc = 1;
	}
	else
		pipex->fd_file1 = f_open(pipex->argv[1], O_RDONLY, 0);
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
	int		fd;
	char	*line;

	fd = f_open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			unlink_err(pipex, "Get next line failed. (here_doc)", 0, ".heredoc_tmp");
		if (ft_strncmp(line, pipex->argv[2], ft_strlen(pipex->argv[2])) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	pipex->fd_file1 = f_open(".heredoc_tmp", O_RDONLY, 0);
	if (pipex->fd_file1 == -1)
		unlink_err(pipex, "Open failed. (here_doc)", 1, ".heredoc_tmp");
}
