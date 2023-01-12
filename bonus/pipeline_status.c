/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:49:32 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/12 12:50:46 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipeline_status(t_pipex *pipex, int i, int pid)
{
	if (i == pipex->argc - 2)
		waitpid(pid, &pipex->status, 0);
}
