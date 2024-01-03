/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:45:27 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:45:30 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

T_BOOL	manage_fd(t_pipes pipes, t_container *book)
{
	if (dup2(pipes.in, STDIN_FILENO) == -1)
		return (FALSE);
	if (dup2(pipes.out, STDOUT_FILENO) == -1)
		return (FALSE);
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
	return (TRUE);
}

T_BOOL	execute_builtins(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (!manage_fd(pipes, book))
		return (ERROR);
	if (book->in_pipe && (!ft_strncmp(leaf->args[0], "cd", 3) \
	|| !ft_strncmp(leaf->args[0], "exit", 5) || !ft_strncmp(leaf->args[0], \
	"export", 7) || !ft_strncmp(leaf->args[0], "unset", 6)))
		return (SUCCESS);
	if (!ft_strncmp(leaf->args[0], "cd", 3))
	{
		if (pipes.out != 1)
			return (SUCCESS);
		return (cd(leaf, book));
	}
	if (!ft_strncmp(leaf->args[0], "echo", 5))
		return (echo(leaf, pipes));
	if (!ft_strncmp(leaf->args[0], "env", 4))
		return (env(leaf, book));
	if (!ft_strncmp(leaf->args[0], "exit", 5))
		my_exit(leaf, book);
	if (!ft_strncmp(leaf->args[0], "export", 7))
		return (export(leaf, book));
	if (!ft_strncmp(leaf->args[0], "pwd", 4))
		return (pwd());
	if (!ft_strncmp(leaf->args[0], "unset", 6))
		return (unset(leaf, book));
	return (ERROR);
}
