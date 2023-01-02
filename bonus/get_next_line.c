/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:27:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/02 11:27:23 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "";
	char		*str;

	if (fd < 0 || read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
		return (0);
	str = malloc(sizeof(char) * 1);
	if (!str)
		return (0);
	str[0] = '\0';
	str = ft_strgrab(str, buf);
	if (!str)
		return (0);
	if (already_contain_next_line(buf))
	{
		ft_remove_line(buf);
		return (str);
	}
	str = get_str(buf, str, fd);
	if (!str)
		return (0);
	ft_remove_line(buf);
	return (str);
}

char	*get_str(char *buf, char *str, int fd)
{
	int	retour;

	retour = 1;
	while ((ft_no_return(buf)) && retour)
	{
		retour = read(fd, buf, BUFFER_SIZE);
		if (retour == -1)
			return (0);
		buf[retour] = '\0';
		str = ft_strgrab(str, buf);
		if (!str)
			return (0);
	}
	if (retour == 0 && str[0] == '\0')
	{
		free(str);
		return (0);
	}
	return (str);
}

