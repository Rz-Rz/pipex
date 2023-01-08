/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:16:57 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/08 21:03:22 by kdhrif           ###   ########.fr       */
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

# include "../libft/libft.h"

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	**cmd;
	char	*path;
	char	**paths;
	char	*cmd_path;
	int		fd[2];
	int		children1;
	int		children2;
	int		status;
	int		fd_file1;
	int		fd_file2;
	int		argc;

}	t_pipex;

// utils.c
int		f_open(char *file, int flag, int mode);
void	get_paths(t_pipex *pipex, char *envp[]);
char	*check_slash(char *str);
char	*get_cmd(t_pipex *pipex, char *cmd);
void	close_fds(t_pipex *pipex);

// error.c
void	generic_err(t_pipex *pipex, char *str, int system);
void	free_pipex(t_pipex *pipex);
void	close_pipex(t_pipex *pipex);

// close.c
void	close_fd(t_pipex *pipex, int *fd, char *error_string);

// success.c
void	success(t_pipex *pipex);

// childs.c
int		exec(t_pipex *pipex, int arg, int stdin, int stdout);

// pipex.c
void	child_exec(t_pipex *pipex);

#endif
