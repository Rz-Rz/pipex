/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:10:46 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:41:50 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	success(t_pipex *pipex)
{
	free_pipex(pipex);
	close_pipex(pipex);
	exit(EXIT_SUCCESS);
}
