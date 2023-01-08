/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:48:40 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:45:08 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fd(t_pipex *pipex, int *fd, char *error_string)
{
	if (close(*fd) == -1)
		generic_err(pipex, error_string, 1);
	else
		*fd = -1;
}
