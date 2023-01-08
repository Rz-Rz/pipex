/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_success.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:00:51 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 09:57:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	success(t_pipex *pipex)
{
	free_pipex(pipex);
	close_pipex(pipex);
	exit(EXIT_SUCCESS);
}
