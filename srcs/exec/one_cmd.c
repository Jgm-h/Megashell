#include "minishell.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], ft_strdup("/"));
	return (paths);
}

char	*find_path(t_container *book, int i, char *arg)
{
	char	**env_paths;
	char	*pathed;

	if (!access(arg, F_OK))
		return (arg);
	env_paths = get_env_paths(book->envp);
	if (!env_paths)
		return (NULL);
	while (env_paths[++i])
	{
		pathed = ft_strjoin(ft_strdup(env_paths[i]), ft_strdup(arg));
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK))
		{
			free_split(env_paths);
			return (pathed);
		}
	}
	return (NULL);
}

void	child(int *pipes_here, t_token *leaf, t_pipes pipes, t_container *book)
{
	if (dup2(STDIN_FILENO, pipes.in) == -1)
		return ;
	if (dup2(STDOUT_FILENO, pipes.out) == -1)
		return ;
	close(STDIN_FILENO);
	if (book->eof_sig && !pipes.in)
	{
		dup2(pipes_here[0], STDIN_FILENO);
		close(pipes_here[0]);
		close(pipes_here[1]);
	}
	execve(leaf->args[0], leaf->args, book->envp);
	my_print_error("minishell: execution failed");
}

void execute(t_token *leaf, t_container *book, t_pipes pipes)
{
	int		pipes_here[2];

	if (book->eof_sig)
	{
		if (pipe(pipes_here) == -1)
			my_perror("pipe", book);
	}
	if (fork1() == 0)
	{
		if (book->eof_sig)
			dup2(pipes_here[1], STDIN_FILENO);
		if (check_builtin(leaf->args[0]))
			execute_builtins(leaf, book, pipes);
		child(pipes_here, leaf, pipes, book);
	}
	if (book->eof_sig)
		manage_heredoc(book);
}

int	exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes)
{
	char	*path;

	leaf->args = ft_split(leaf->argv, ' ');
	if (!leaf->args)
		return (FALSE);
	path = find_path(book, -1, leaf->args[0]);
	if (!path)
	{
		ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
		ft_putstr_fd(leaf->args[0], STDERR_FILENO);
		ft_putstr_fd((char *)": command not found\n", STDERR_FILENO);
		book->exit_status = 127;
		return (FALSE);
	}
	free(leaf->args[0]);
	leaf->args[0] = path;
	execute(leaf, book, pipes);
	if (pipes.in != 0)
		close(pipes.in);
	if (pipes.out != 1)
		close(pipes.out);
	book->nmbr_exec++;
	return (SUCCESS);
}
