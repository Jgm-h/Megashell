/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:48:09 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:48:10 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

unsigned int	expand(char **input, t_container *book, int i)
{
	int		j;

	j = 0;
	if ((*input)[i + 1] == '?')
		return (ft_expand_exit(input, i, book));
	while (book->envp[++j])
	{
		if (!ft_strcmp_lexer(&(*input)[i + 1], (book->envp[j])))
			return (ft_strcpy_lexer(input, i, book->envp[j] \
					+ ft_keysize(book->envp[j]), -1));
	}
	return (ft_strcpy_lexer(input, i, NULL, -1));
}

unsigned int	ft_expand_exit(char **input, int i, t_container *book)
{
	char	*exit_status;
	char	*reste;
	char	*debut;
	int		j;

	j = 0;
	exit_status = ft_itoa(book->exit_status);
	reste = ft_strdup(&(*input)[i + 2]);
	debut = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		debut[j] = (*input)[j];
		j++;
	}
	debut = ft_strjoin(debut, exit_status);
	(*input) = ft_strjoin(debut, reste);
	return (TRUE);
}

unsigned int	ft_strcpy_lexer(char **input, int i, char *env, int j)
{
	int		k;
	int		key_size;
	char	*exp;

	exp = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(*input) + ft_strlen(env) \
			- ft_keysize_input((*input) + i) + 1, sizeof (char));
	if (!*input || !exp)
		ft_putstr_fd("malloc", 2);
	while (++j < i)
		(*input)[j] = exp[j];
	k = -1;
	if (env)
	{
		while (env[++k])
			(*input)[j + k] = env[k];
	}
	key_size = ft_keysize_input(&(exp[i]));
	while (exp[j + key_size])
		(*input)[j + k++] = exp[j + key_size++];
	(*input)[j + k] = 0;
	return (TRUE);
}

void	c_qts(char **input, int i)
{
	int		j;
	char	c;

	while ((*input)[i])
	{
		if (input[0][i] == '*')
			(*input)[i] = 1;
		if ((*input)[i] == '\"' || (*input)[i] == '\'')
		{
			c = (*input)[i];
			j = i;
			while ((*input)[j] && (*input)[j + 1] != c)
			{
				(*input)[j] = (*input)[j + 1];
				j++;
				i++;
			}
			(*input)[j] = 0;
		}
		else
			i++;
	}
}
