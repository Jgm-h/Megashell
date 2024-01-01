#include "minishell.h"

volatile extern int	g_status;

void	add_var(t_container *book, char *key, char *value)
{
	int		i;
	char	**old_envp;
	char	**hook;

	i = 0;
	while (book->envp[i])
		i++;
	old_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (book->envp[++i])
		old_envp[i] = ft_strdup(book->envp[i]);
	hook = book->envp;
	book->envp = ft_calloc(i + 2, sizeof (char *));
	i = -1;
	while (old_envp[++i])
		book->envp[i] = ft_strdup(old_envp[i]);
	book->envp[i] = ft_strjoin(key, value);
	i = -1;
	while (hook[++i])
	{
		free(hook[i]);
		free(old_envp[i]);
	}
	free(hook);
	free(old_envp);
}

void	export_value(char **env, char *key, char *value)
{
	char	*hook;

	hook = (*env);
	(*env) = ft_strjoin(key, value);
	if (!(*env))
		ft_putstr_fd("malloc error", 2);
	free(hook);
}

int	get_index_env(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}

T_BOOL	my_access(char *file, int flag)
{
	if (access(file, flag) == -1)
	{
		ft_putstr_fd("minishell-2.0: permission denied: ", 2);
		ft_putstr_fd(file, 2);
		return (FALSE);
	}
	else
		return (TRUE);
}

int	my_dup2(int fd_file, int to_dup)
{
	if (dup2(fd_file, to_dup) == -1)
	{
		ft_putstr_fd("minishell-2.0: dup2 failed", 2);
		return (-1);
	}
	else
		return (1);
}
