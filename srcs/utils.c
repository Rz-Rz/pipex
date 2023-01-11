/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:14:00 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 16:09:16 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	f_open(char *file, int flag, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flag);
	else
		fd = open(file, flag, mode);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}

void	get_paths(t_pipex *pipex, char *envp[])
{
	while (*envp != NULL && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (ft_strncmp(*envp, "PATH=", 5) == 0)
	{
		pipex->is_path = 1;
		pipex->path = ft_strdup(*envp + 5);
		if (pipex->path == NULL)
			generic_err(pipex, "Malloc error\
					. (get_paths -> ft_strdup)", 0, EXIT_FAILURE);
		pipex->paths = ft_split(pipex->path, ':');
		if (pipex->paths == NULL)
			generic_err(pipex, "Malloc error\
					. (get_paths -> ft_split)", 0, EXIT_FAILURE);
	}
	else
		pipex->is_path = 0;
}

char	*get_cmd(t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = check_fpath(pipex, cmd);
	if (tmp != NULL)
		return (ft_strdup(tmp));
	if (pipex->is_path == 0)
		generic_err(pipex, cmd, 3, CMD_NOT_FOUND);
	i = -1;
	while (pipex->paths[++i])
	{
		check_slash(pipex->paths[i]);
		tmp = ft_strjoin(pipex->paths[i], "/");
		null_str_err(pipex, tmp);
		tmp2 = tmp;
		tmp = ft_strjoin(tmp, cmd);
		null_str_err(pipex, tmp);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			free(tmp2);
			return (tmp);
		}
		free(tmp);
		free(tmp2);
	}
	return (NULL);
}

char	*check_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '/')
		str[i - 1] = '\0';
	return (str);
}

void	close_fds(t_pipex *pipex)
{
	close(pipex->fd_file1);
	close(pipex->fd[0]);
	close(pipex->fd_file2);
}
