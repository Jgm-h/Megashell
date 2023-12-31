#include "minishell.h"

/* this builtin should print the working directory using getcwd
 * getcwd space needs to be freed
 * */

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	errno = 0;
	return (0);
}
