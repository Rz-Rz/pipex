/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:51:38 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:57:46 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipe_fd(t_pipex *pipex, int *fd, char *error_string)
{
	if (pipe(fd) == -1)
		generic_err(pipex, error_string, 1);
}
