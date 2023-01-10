
#include "../includes/pipex_bonus.h"

char	*check_fpath(t_pipex *pipex, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			generic_err(pipex, cmd, 1);
			return ((char *)0);
		}
	}
	else
		return ((char *)0);
}
