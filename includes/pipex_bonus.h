/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:16:57 by kdhrif            #+#    #+#             */
/*   Updated: 2023/01/12 12:51:44 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

# include "../bonus/get_next_line.h"

# include "../libft/libft.h"

# define CMD_NOT_FOUND 127

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	**cmd;
	char	*path;
	char	**paths;
	char	*file1;
	char	*file2;
	char	*cmd_path;
	int		heredoc;
	int		fd[2];
	int		children1;
	int		children2;
	int		pid;
	int		status;
	int		fd_file1;
	int		fd_file2;
	int		argc;
	int		is_path;
}	t_pipex;

// utils.c
int		f_open(char *file, int flag, int mode);
void	get_paths(t_pipex *pipex, char *envp[]);
char	*check_slash(char *str);
char	*get_cmd(t_pipex *pipex, char *cmd);

// error.c
void	generic_err(t_pipex *pipex, char *str, int system, int exitcode);
void	free_pipex(t_pipex *pipex);
void	close_pipex(t_pipex *pipex);
int		ft_strcmp(const char *s1, const char *s2);

// utils_2.c
char	*check_fpath(t_pipex *pipex, char *cmd);

// pipeline_status.c
void	pipeline_status(t_pipex *pipex, int i, int pid);

// exit_macro.c
int		exit_macro(int status);

// exception.c
void	wrg_infile(t_pipex *pipex);

// pipe.c
void	pipe_fd(t_pipex *pipex, int *fd, char *error_string);

// fork.c
void	fork_pid(t_pipex *pipex, int *pid, char *error_string);

// close.c
void	close_fd(t_pipex *pipex, int *fd, char *error_string);

// freestr
void	freestr(char *s1, char *s2);

// path_null.c
void	path_null(t_pipex *pipex, char *cmd);

// null_str_err
void	null_str_err(t_pipex *pipex, char *str);

// childs.c
int		exec(t_pipex *pipex, int arg, int stdin, int stdout);

// pipex.c
void	child_exec(t_pipex *pipex);

// bonus_success.c
void	success(t_pipex *pipex);

// child bonus
int		exec_bonus(t_pipex *pipex, char *cmd, int stdin, int stdout);

// here_doc.c
void	here_doc(t_pipex *pipex);
void	check_mode_infile(t_pipex *pipex, int *i);
void	check_mode_outfile(t_pipex *pipex);
void	put_heredoc(t_pipex *pipex);
int		heredoc_cmp(char *line, t_pipex *pipex);

#endif
