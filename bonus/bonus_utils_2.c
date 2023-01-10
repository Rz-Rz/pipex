/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:49:59 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/10 21:50:20 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			generic_err(pipex, cmd, 1);
			return ((char *)0);
		}
	}
	else
		return ((char *)0);
}
