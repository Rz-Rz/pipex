/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_str_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:45:46 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/11 14:56:35 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <stdlib.h>

void	null_str_err(t_pipex *pipex, char *str)
{
	if (str == NULL)
		generic_err(pipex, "Malloc error. (get_cmd -> ft_strjoin)\n"\
				, 0, EXIT_FAILURE);
}
