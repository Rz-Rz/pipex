/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:42:05 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 16:07:12 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			if (pipex->is_path == 0)
				generic_err(pipex, cmd, 3, CMD_NOT_FOUND);
			else
				generic_err(pipex, cmd, 1, CMD_NOT_FOUND);
			return ((char *)0);
		}
	}
	else
		return ((char *)0);
}
