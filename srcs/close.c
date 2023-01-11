/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:43:12 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 09:40:52 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fd(t_pipex *pipex, int *fd, char *error_string)
{
	if (close(*fd) == -1)
		generic_err(pipex, error_string, 1, EXIT_FAILURE);
	else
		*fd = -1;
}
