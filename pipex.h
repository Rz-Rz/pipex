/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:16:57 by kdhrif            #+#    #+#             */
/*   Updated: 2022/12/28 20:48:04 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* write, read, close, access, pipe, dup, dup2, excve, fork*/
/* STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO */
# include <unistd.h>
# include <sys/types.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
/* O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND */
# include <fcntl.h>

/* wait, waitpid */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/* perror */
# include <stdio.h>

/* errno */
# include <errno.h>

# include "libft/libft.h"

/* # define EXIT_SUCCESS 0 */
/* # define EXIT_FAILURE -1 */

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*path;
	char 	**paths;
	char	*file1;
	char	*file2;
	char	*cmd1_path;
	char	*cmd2_path;
	int		fd[2];
	int		children1;
	int		children2;
	int		status;
	int		fd_file1;
	int		fd_file2;

}	t_pipex;

// utils.c
int		f_open(char *file, int flag, int mode);
void	get_paths(t_pipex *pipex, char *envp[]);
char	*check_slash(char *str);
char	*get_cmd(t_pipex *pipex, char *cmd);

// error.c
void	generic_err(t_pipex *pipex, char *str, int system);
void	free_pipex(t_pipex *pipex);

// childs.c
int	exec(t_pipex *pipex, char *argv[], char *envp[], int arg);


#endif
