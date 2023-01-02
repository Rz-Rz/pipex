/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:24:40 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/02 11:24:50 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strgrab(char *str, char *buf);
char	*get_str(char *buf, char *str, int fd);
void	ft_remove_line(char *buf);
int		already_contain_next_line(char *buf);
int		ft_no_return(char *str);
#endif
