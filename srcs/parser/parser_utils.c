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

char	*parenthese_trim(char *prompt)
{
	int	i;

	i = ft_strlen(prompt);
	prompt[0] = 0;
	if (prompt[i - 1] != ')')
		return (NULL);
	prompt[i - 1] = 0;
	return (&prompt[1]);
}

char	*trim_space(char *prompt)
{
	int	i;

	if (prompt == 0 || prompt[0] == 0)
		return (0);
	i = ft_strlen(prompt);
	while (--i >= 0 && iswhitespace(prompt[i]))
		;
	prompt[i + 1] = 0;
	i = -1;
	while (iswhitespace(prompt[++i]))
		;
	if (i > 0)
		prompt[i - 1] = 0;
	return (&prompt[i]);
}

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
