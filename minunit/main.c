

#include "minunit.h"
#include <fcntl.h>
#include "../includes/pipex.h"

int		x = 10;
int		y = 30;

char	*check_fpath(t_pipex *pipex, char *cmd)
{
	char	*tmp;

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

void	setup(void)
{
}
void	teardown(void)
{
}

MU_TEST(example)
{
	t_pipex *pipex;
	char *cmd = "ls";
	mu_assert_int_eq(0, (int)check_fpath(pipex, cmd) );
}

MU_TEST_SUITE(test_suite_tokens)
{
	MU_SUITE_CONFIGURE(&setup, &teardown);
	MU_RUN_TEST(example);
}

int	main(void)
{
	MU_RUN_SUITE(test_suite_tokens);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
