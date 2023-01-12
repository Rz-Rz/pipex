/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:44:59 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/12 12:47:35 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	wrg_infile(t_pipex *pipex)
{
	if (pipex->fd_file1 == -2)
	{
		pipex->fd_file1 = -1;
		generic_err(pipex, NULL, 0, EXIT_FAILURE);
	}
}
