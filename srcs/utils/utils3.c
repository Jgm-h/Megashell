/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:15:04 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/03 21:15:07 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile extern int	g_status;

void	restore_fds(t_container *book, t_pipes pipe)
{
	dup2(book->o_fdout, STDOUT_FILENO);
	dup2(book->o_fdin, STDIN_FILENO);
	dup2(book->o_fdin, pipe.in);
	dup2(book->o_fdout, pipe.out);
}

T_BOOL	check_empty_prompt(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (FALSE);
	return (TRUE);
}

void	write_heredoc(t_container *book, char *input, char *to_send)
{
	while (g_status == HEREDOC)
	{
		input = readline("> ");
		if (!input)
			continue ;
		if (!ft_strncmp(input, book->eof, ft_strlen(book->eof) + 1))
		{
			write(book->pipe_here[1], to_send, ft_strlen(to_send));
			free(input);
			break ;
		}
		to_send = ft_strjoin(to_send, input);
		to_send = ft_strjoin(to_send, ft_strdup("\n"));
	}
}
