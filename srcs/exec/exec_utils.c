/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:46:23 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:46:25 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	pipes_management(t_pipes pipes, t_container *book, t_token *leaf)
{
	if (pipes.in != 0)
		close(pipes.in);
	if (pipes.out != 1)
		close(pipes.out);
	if (check_builtin(leaf->args[0]) != 2)
		book->nmbr_exec++;
}

T_BOOL	path_error(t_token *leaf, t_container *book)
{
	ft_putstr_fd((char *)"minishell: ", 2);
	ft_putstr_fd(leaf->args[0], 2);
	ft_putstr_fd((char *)": command not found\n", 2);
	book->exit_status = 127;
	return (ERROR);
}

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		errno = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		errno = WTERMSIG(status);
}
