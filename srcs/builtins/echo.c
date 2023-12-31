#include "builtins.h"

T_BOOL	echo(t_token *leaf, t_pipes pipes)
{
	T_BOOL	option;
	int		i;

	i = 1;
	option = FALSE;
	if (!ft_strncmp(leaf->args[1], "-n", 3))
	{
		option = TRUE;
		i++;
	}
	while (leaf->args[i])
		ft_putstr_fd(leaf->args[i++], pipes.out);
	if (option)
		return (SUCCESS);
	ft_putstr_fd("\n", pipes.out);
	errno = 0;
	return (SUCCESS);
}
