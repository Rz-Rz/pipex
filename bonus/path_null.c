/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:07:20 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 17:34:03 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	path_null(t_pipex *pipex, char *cmd)
{
	if (pipex->is_path == 0)
		generic_err(pipex, cmd, 3, CMD_NOT_FOUND);
}
