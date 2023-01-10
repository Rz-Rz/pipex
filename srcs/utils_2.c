

#include "../includes/pipex.h"

char	*check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			generic_err(pipex, "Command not found", 0);
			return ((char *)0);
		}
	}
	else
		return ((char *)0);
}

