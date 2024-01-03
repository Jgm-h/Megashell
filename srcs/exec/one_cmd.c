/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:46:29 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:46:30 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "exec.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
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

void	child(t_token *leaf, t_pipes pipes, t_container *book)
{
	if (dup2(pipes.in, STDIN_FILENO) == -1)
		return ;
	if (dup2(pipes.out, STDOUT_FILENO) == -1)
		return ;
	if (pipes.in != 0)
		close(pipes.in);
	if (pipes.out != 1)
		close(pipes.out);
	if (book->eof_sig)
	{
		dup2(book->pipe_here[0], STDIN_FILENO);
		close(book->pipe_here[0]);
		close(book->pipe_here[1]);
	}
	execve(leaf->args[0], leaf->args, book->envp);
	ft_putstr_fd("minishell: execution failed\n", 2);
}

void	execute(t_token *leaf, t_container *book, t_pipes pipes)
{
	int	pid;

	if (book->eof_sig)
	{
		if (pipe(book->pipe_here) == -1)
			ft_putstr_fd("pipe", 2);
	}
	pid = fork1();
	if (pid == 0)
	{
		if (check_builtin(leaf->args[0]))
		{
			execute_builtins(leaf, book, pipes);
			exit(errno);
		}
		child(leaf, pipes, book);
	}
	if (book->eof_sig)
		manage_heredoc(book);
}

int	exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes)
{
	char	*path;
	T_BOOL	ret;

	if (leaf->right && !execute_redir(leaf, book, pipes))
		return (FALSE);
	if (check_builtin(leaf->args[0]) == 1)
		execute(leaf, book, pipes);
	else if (check_builtin(leaf->args[0]) == 2 && !book->in_pipe)
	{
		ret = execute_builtins(leaf, book, pipes);
		restore_fds(book, pipes);
		return (ret);
	}
	else
	{
		path = find_path(book, -1, leaf->args[0]);
		if (!path)
			return (path_error(leaf));
		if (path != leaf->args[0])
			free(leaf->args[0]);
		leaf->args[0] = path;
		execute(leaf, book, pipes);
	}
	pipes_management(pipes, book, leaf);
	return (SUCCESS);
}
