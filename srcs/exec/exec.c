/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:46:08 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:46:10 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

volatile extern int	g_status;

T_BOOL	execute_pipe(t_token *leaf, t_container *book, t_pipes pipes)
{
	t_pipes	left;
	t_pipes	right;
	t_pipes	_pipe;

	left = pipes;
	right = pipes;
	pipe((int *)&_pipe);
	book->in_pipe = TRUE;
	left.out = _pipe.out;
	right.in = _pipe.in;
	r_executor(leaf->left, book, left);
	r_executor(leaf->right, book, right);
	book->in_pipe = FALSE;
	return (SUCCESS);
}

T_BOOL	exec_and(t_token *leaf, t_container *book, t_pipes pipes)
{
	int	status;

	r_executor(leaf->left, book, pipes);
	while (book->nmbr_exec)
	{
		waitpid(0, &status, 0);
		handle_exit_status(status);
		book->nmbr_exec--;
	}
	if (g_status == ABORT_HEREDOC || errno)
		return (ERROR);
	r_executor(leaf->right, book, pipes);
	while (book->nmbr_exec)
	{
		waitpid(0, &status, 0);
		handle_exit_status(status);
		book->nmbr_exec--;
	}
	if (errno)
		return (ERROR);
	return (SUCCESS);
}

T_BOOL	exec_or(t_token *leaf, t_container *book, t_pipes pipes)
{
	int		status;
	T_BOOL	ret;

	ret = r_executor(leaf->left, book, pipes);
	while (book->nmbr_exec)
	{
		waitpid(0, &status, 0);
		handle_exit_status(status);
		book->nmbr_exec--;
	}
	if (!ret)
		return (SUCCESS);
	if (g_status == ABORT_HEREDOC)
		return (ERROR);
	r_executor(leaf->right, book, pipes);
	while (book->nmbr_exec)
	{
		waitpid(0, &status, 0);
		handle_exit_status(status);
		book->nmbr_exec--;
	}
	if (errno)
		return (ERROR);
	return (SUCCESS);
}

T_BOOL	r_executor(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (g_status == EXECUTION)
	{
		if (!leaf)
			return (SUCCESS);
		else if (leaf->type == AND)
			return (exec_and(leaf, book, pipes));
		else if (leaf->type == OR)
			return (exec_or(leaf, book, pipes));
		else if (leaf->type == PIPE)
			return (execute_pipe(leaf, book, pipes));
		else if (leaf->type == COMMAND)
			return (exec_one_cmd(leaf, book, pipes));
	}
	return (ERROR);
}

void	exec(t_container *book)
{
	struct s_pipes	pipes;
	int				status;

	book->o_fdout = dup(STDOUT_FILENO);
	book->o_fdin = dup(STDIN_FILENO);
	pipes.in = STDIN_FILENO;
	pipes.out = STDOUT_FILENO;
	g_status = EXECUTION;
	if (r_executor(book->head, book, pipes) == ERROR && \
	(book->head->type == AND || book->head->type == OR))
		book->exit_status = errno;
	if (book->head->type != AND && book->head->type != OR)
	{
		while (book->nmbr_exec)
		{
			waitpid(0, &status, 0);
			handle_exit_status(status);
			book->nmbr_exec--;
		}
		book->exit_status = errno;
	}
}
