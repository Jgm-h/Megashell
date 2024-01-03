/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:50:18 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:50:20 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile extern int	g_status;

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		free(split[i++]);
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

void	manage_heredoc(t_container *book)
{
	char	*input;
	char	*to_send;

	to_send = NULL;
	g_status = HEREDOC;
	write_heredoc(book, input, to_send);
	if (g_status == HEREDOC)
		g_status = EXECUTION;
	if (g_status == ABORT_HEREDOC)
		errno = 1;
	close(book->pipe_here[1]);
	close(book->pipe_here[0]);
	book->eof_sig = FALSE;
}

int	check_builtin(char *str)
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
