#include "minishell.h"

int	env(t_token *leaf, t_container *book)
{
	int	i;

	i = 0;
	if (leaf->args[1])
	{
		ft_putstr_fd("env:", 2);
		ft_putstr_fd(leaf->args[1], 2);
		ft_putstr_fd(": No such file or directory", 2);
		errno = 127;
		return (ERROR);
	}
	while (book->envp[i])
	{
		printf("%s\n", book->envp[i]);
		i++;
	}
	errno = 0;
	return (SUCCESS);
}
