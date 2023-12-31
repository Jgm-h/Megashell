/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:09:53 by albaud            #+#    #+#             */
/*   Updated: 2023/12/30 22:13:44 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

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

int skip_quotes(char *prompt, int i)
{
	char	c;

	c = prompt[i];
	while (prompt[++i] && prompt[i] != c)
		;
	return (i);
}

int	find_level(char *prompt, int level)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {
			"&&", "||", "|"};

	len = ft_strlen(strings[level]);
	i = -1;
	parenthese_level = 0;
	while (prompt[++i])
	{
		if (prompt[i] ==  '"' || prompt[i] == '\'')
			i = skip_quotes(prompt, i);
		parenthese_level += (prompt[i] == '(') - (prompt[i] == ')');
		if (parenthese_level != 0
			|| ft_strncmp(&prompt[i], strings[level], len))
			continue ;
		prompt[i] = 0;
		prompt[i + (len > 1)] = 0;
		return (i + len);
	}
	return (-1);
}

int	print_syntax_error(char *message)
{
	printf("Minishell: syntax error near unexpected token `%s`\n", message);
	return (1);
}

int	syntax_error(char *prompt)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {
			"&&", "||", "|", "<<", "<", ">>", ">" };

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(strings[i]);
		if (ft_strncmp(prompt, strings[i], len) == 0
			|| ft_strncmp(&prompt[strlen(prompt) - len], strings[i], len) == 0)
			return (print_syntax_error(strings[i]));
	}
	i = -1;
	parenthese_level = 0;
	while (prompt[++i])
	{
		parenthese_level += (prompt[i] == '(') - (prompt[i] == ')');
		if (parenthese_level < 0)
			return (print_syntax_error(")"));
	}
	if (parenthese_level != 0)
		return (print_syntax_error("("));
	return (0);
}

t_token	*parser(char *prompt)
{
	t_token	*res;
	int		i;
	int		index;

	if (!prompt || !*prompt)
		return (NULL);
	res = ft_calloc(1, sizeof(t_token));
	prompt = trim_space(prompt);
	if (syntax_error(prompt))
		return (NULL);
	i = -1;
	index = -1;
	while (++i < 3 && index == -1)
		index = find_level(prompt, i);
	if (index == -1)
	{
		if (prompt[0] == '(')
			return (parser(parenthese_trim(prompt)));
		res->type = COMMAND;
		res->argv = strdup(prompt);
		res->right = redir(prompt);
		return (res);
	}
	res->type = i - 1;
	if (prompt)
	{
		res->left = parser(prompt);
		if (res->left == NULL)
			return (NULL);
	}
	if (prompt[index])
	{
		res->right = parser(&prompt[index]);
		if (res->right == NULL)
			return (NULL);
	}
	return (res);
}
