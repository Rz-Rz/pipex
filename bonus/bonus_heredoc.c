/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 22:33:49 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/01 22:36:37 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void   check_mode(t_pipex *pipex)
{
	if (ft_strncmp("here_doc", pipex->argv[1], 8) == 0)
		here_doc(pipex);
}

void   here_doc(t_pipex *pipex)
{
	int   fd;
	char *line;

	fd = f_open(pipex->argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, pipex->argv[3], ft_strlen(pipex->argv[3])) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}
