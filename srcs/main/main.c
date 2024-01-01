/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:48:50 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:48:52 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

volatile int	g_status = NEW_LINE;

int	main(int argc, char **argv, char **envp)
{
	t_container	*book;

	(void) argc;
	(void) argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (!init(&book, envp, argc))
		return (1);
	return (minishell(book));
}
