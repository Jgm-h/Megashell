#include "minishell.h"
volatile extern int	g_status;

void	replace_path(t_token *leaf, char *pwd)
{
	int		i;
	int		j;
	char	*new_str;

	j = 0;
	i = ft_strlen(pwd);
	new_str = ft_calloc(ft_strlen(leaf->args[1]) - \
			ft_strlen(pwd) + 1, sizeof (char));
	while (leaf->args[1][i])
		new_str[j++] = leaf->args[1][i++];
	new_str[j] = 0;
	free(leaf->args[1]);
	leaf->args[1] = new_str;
}

/* need to remalloc the whole envp*/
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
	if (!env)
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

void	free_split(char **to_free)
{
	int		i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void manage_heredoc(t_container *book)
{
	char	*input;

	if (!book->eof_sig)
		return ;
	g_status = HEREDOC;
	while (g_status == HEREDOC)
	{
		input = readline("> ");
		if (!input)
			continue ;
		if (ft_strncmp(input, book->eof, ft_strlen(book->eof) + 1))
			continue ;
		write(book->pipe_here[1], input, ft_strlen(input));
	}
	if (g_status == HEREDOC)
		g_status = EXECUTION;
	if (g_status == ABORT_HEREDOC)
		errno = 1;
	close(book->pipe_here[1]);
	close(book->pipe_here[0]);
	book->eof_sig = FALSE;
}

int check_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 3))
		return (2);
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	if (!ft_strncmp(str, "env", 4))
		return (1);
	if (!ft_strncmp(str, "exit", 5))
		return (2);
	if (!ft_strncmp(str, "export", 7))
		return (2);
	if (!ft_strncmp(str, "pwd", 4))
		return (1);
	if (!ft_strncmp(str, "unset", 6))
		return (2);
	return (0);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		array[i] = NULL;
		free(array[i++]);
	}
	array = NULL;
	free(array);
}
