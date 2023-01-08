/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:14:00 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:46:38 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	get_paths(t_pipex *pipex, char *envp[])
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	pipex->path = ft_strdup(*envp + 5);
	if (pipex->path == NULL)
		generic_err(pipex, "Malloc error. (get_paths -> ft_strdup)", 0);
	pipex->paths = ft_split(pipex->path, ':');
	if (pipex->paths == NULL)
		generic_err(pipex, "Malloc error. (get_paths -> ft_split)", 0);
}

char	*get_cmd(t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	while (pipex->paths[++i])
	{
		check_slash(pipex->paths[i]);
		tmp = ft_strjoin(pipex->paths[i], "/");
		tmp2 = tmp;
		if (tmp == NULL)
			generic_err(pipex, "Malloc error. (get_cmd -> ft_strjoin)", 0);
		tmp = ft_strjoin(tmp, cmd);
		if (tmp == NULL)
			generic_err(pipex, "Malloc error. (get_cmd -> ft_strjoin)", 0);
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
