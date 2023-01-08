/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:54:28 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 20:56:28 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	fork_pid(t_pipex *pipex, int *pid, char *error_string)
{
	*pid = fork();
	if (*pid == -1)
		generic_err(pipex, error_string, 1);
}
