/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:09:53 by albaud            #+#    #+#             */
/*   Updated: 2024/01/01 23:50:47 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <string.h>

int	find_level(char *prompt, int level)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {"&&", "||", "|"};

	len = ft_strlen(strings[level]);
	i = -1;
	parenthese_level = 0;
	while (prompt[++i])
	{
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

int	syntax_error(char *prompt)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {"&&", "||", "|", "<<", "<", ">>", ">" };

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

t_token	*parse_command(char *prompt)
{
	t_token	*res;

	if (prompt[0] == '(')
		return (parser(parenthese_trim(prompt)));
	res = ft_calloc(1, sizeof(t_token));
	res->type = COMMAND;
	res->right = redir(prompt, -1, NULL, NULL);
	res->argv = strdup(prompt);
	return (res);
}

t_token	*parser(char *prompt)
{
	t_token	*res;
	int		i;
	int		index;

	prompt = trim_space(prompt);
	if (!prompt || !*prompt || syntax_error(prompt))
		return (NULL);
	i = -1;
	index = -1;
	while (++i < 3 && index == -1)
		index = find_level(prompt, i);
	if (index == -1)
		return (parse_command(prompt));
	res = ft_calloc(1, sizeof(t_token));
	res->type = i - 1;
	res->left = parser(prompt);
	if (res->left == NULL)
		return (NULL);
	res->right = parser(&prompt[index]);
	if (res->right == NULL)
		return (NULL);
	return (res);
}
