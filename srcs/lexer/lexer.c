/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:47:45 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:47:47 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

T_BOOL	expand_variables(char **input, t_container *book)
{
	int	i;
	int	tmp;

	i = 0;
	while ((*input)[i])
	{
		if (check_state((*input), i, FALSE, \
				FALSE) && check_expand((*input), i, book))
		{
			tmp = ft_value_expand(&(*input)[i + 1], book->envp);
			if (!expand(input, book, i))
				return (FALSE);
			i += tmp;
		}
		else
			i++;
	}
	return (TRUE);
}

int	ft_small_split(char *str, char **to_copy)
{
	int		i;
	char	c;
	T_BOOL	check;

	check = TRUE;
	(*to_copy) = ft_calloc(get_len_split(str), sizeof (char));
	c = find_sep(str);
	i = 0;
	while (str[i])
	{
		if (c == ' ' && str[i] == ' ')
			break ;
		else if (check && str[i] == c && c != ' ')
			check = !check;
		else if (!check && str[i] == c && c != ' ')
		{
			(*to_copy)[i] = str[i];
			i++;
			break ;
		}
		(*to_copy)[i] = str[i];
		i++;
	}
	return (i);
}

int	check_valid_split(char *input)
{
	char	c;
	int		i;

	i = 0;
	if (input[i] == '"' || input[i] == '\'')
	{
		c = input[i];
		i++;
		while (input[i] && input[i] != c)
			i++;
	}
	if (i == 1)
		return (2);
	return (0);
}

void	split_var(char *input, t_token *leaf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc(input, leaf, FALSE, FALSE);
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		i += check_valid_split(&input[i]);
		if (!input[i])
			break ;
		i += ft_small_split(&input[i], &(leaf->args[j]));
		j++;
	}
}

T_BOOL	lexer(char **input)
{
	if (!check_empty_prompt(*input))
		return (FALSE);
	if (!check_closed_quotes(*input, 0, 0))
		return (FALSE);
	if (!check_heredoc_alone(*input, 0, FALSE))
		return (FALSE);
	return (TRUE);
}
