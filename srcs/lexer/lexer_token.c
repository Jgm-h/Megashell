/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:51:26 by albaud            #+#    #+#             */
/*   Updated: 2024/01/01 23:52:29 by albaud           ###   ########.fr       */
=======
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:48:03 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:48:05 by jmorcom-         ###   ########.fr       */
>>>>>>> b7894c60982057ed925bf32d5e988d80d2b7e739
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc(char *input, t_token *leaf, T_BOOL simp, T_BOOL doub)
{
	int	i;

	i = 0;
	while (*input)
	{
		while (*input && ((*input == ' ' && !simp && !doub) || \
			(*input == '\'' && !doub) || (*input == '\"' && !simp)))
		{
			if (*input == '\"' && !simp)
				doub = !doub;
			if (*input == '\'' && !doub)
				simp = !simp;
			input++;
		}
		if (!*input)
			continue ;
		i++;
		while (*input && !((*input == ' ' && !simp && !doub) || \
		(*input == '\'' && !doub) || (*input == '\"' && !simp)))
			input++;
	}
	leaf->args = ft_calloc(i + 1, sizeof(char *));
}

int	get_len_split(char *str)
{
	char	c;
	int		i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		c = str[i];
	else
		c = ' ';
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	find_sep(char *str)
{
	if (*str == '"' || *str == '\'')
		return (*str);
	else
		return (' ');
}

char	**prendlewildcardetwildcardmoicasalpouilleuxdesclave(char **args, int i)
{
	char	**res;
	char	**wild;

	wild = wildcard(args[i]);
	res = strs_insert(args, wild, i);
	free(wild);
	free(args);
	return (res);
}

T_BOOL	lexer_token(t_token *leaf, t_container *book)
{
	int	i;

	i = 0;
	if (!leaf)
		return (TRUE);
	if (leaf->type != COMMAND)
		return (lexer_token(leaf->left, book) && \
				lexer_token(leaf->right, book));
	if (leaf->type == COMMAND || leaf->type == IN_REDIR || \
	leaf->type == OUT_REDIR || leaf->type == HEREDOC || leaf->type == APD_REDIR)
	{
		split_var(leaf->argv, leaf);
		while (leaf->args[i])
		{
			if (!expand_variables(&(leaf->args[i]), book))
				return (FALSE);
			c_qts(&(leaf->args[i++]), 0, 0, 0);
			if (ft_strchr(leaf->args[i - 1], '*'))
				leaf->args = prendlewildcardetwildcardmoicasalpouilleuxdesclave
					(leaf->args, i - 1);
			c_qts(&(leaf->argv), 0, 0, 0);
		}
		return (TRUE);
	}
	return (FALSE);
}
