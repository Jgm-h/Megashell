/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:49:22 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:49:24 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_syntax_error(char *message)
{
	printf("Minishell: syntax error near unexpected token `%s`\n", message);
	return (1);
}

int	skip_quotes(char *prompt, int i)
{
	char	c;

	if (prompt[i] != '"' && prompt[i] != '\'')
		return (i);
	c = prompt[i];
	while (prompt[++i] && prompt[i] != c)
		;
	return (i);
}

int	iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
