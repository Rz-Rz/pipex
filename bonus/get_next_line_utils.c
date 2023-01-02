/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:25:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/02 11:29:22 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_remove_line(char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i] != '\0')
		buf[j++] = buf[i++];
	buf[j++] = buf[i++];
}

int	already_contain_next_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_no_return(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strgrab(char *str, char *buf)
{
	char	*new_str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (str[j])
		j++;
	new_str = malloc(sizeof(char) * (i + j + 1));
	if (!new_str)
		return (0);
	while (str[++k])
		new_str[k] = str[k];
	k = -1;
	while (++k < i)
		new_str[j + k] = buf[k];
	new_str[j + k] = '\0';
	free(str);
	return (new_str);
}
