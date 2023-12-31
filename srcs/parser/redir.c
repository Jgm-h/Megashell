/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:49:30 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/02 01:14:20 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	cpy(char *a, char *b)
{
	while (*b)
	{
		*a = *b;
		b++;
		a++;
	}
	*a = 0;
}

t_token	*get_redir(char *prompt, int i, char *redire_type, int redire_index)
{
	t_token	*res;
	int		j;
	char	*ret;
	int		start;

	j = i + strlen(redire_type);
	while (prompt[j] && iswhitespace(prompt[j]))
		j++;
	start = j;
	while (prompt[j] && !iswhitespace(prompt[j]))
	{
		j = skip_quotes(prompt, j);
		j++;
	}
	ret = ft_calloc(j - start + 1, sizeof (char));
	ft_strlcpy(ret, &prompt[start], j - start + 1);
	res = ft_calloc(1, sizeof(t_token));
	res->type = redire_index + HERDOC;
	res->argv = ret;
	cpy(&prompt[i], &prompt[j]);
	return (res);
}

t_token	*redir(char *prompt, int i, t_token *res, t_token *tmp)
{
	t_token		*tmp2;
	int			j;
	static char	*strings[] = {"<<", ">>", "<", ">" };

	while (prompt[i++])
	{
		i = skip_quotes(prompt, i);
		j = -1;
		while (++j < 4)
		{
			if (ft_strncmp(&prompt[i], strings[j], strlen(strings[j])))
				continue ;
			tmp2 = get_redir(prompt, i, strings[j], j);
			if (res == 0)
				res = tmp2;
			if (tmp)
			{
				tmp->right = tmp2;
				tmp = tmp2;
			}
			else
				tmp = tmp2;
		}
	}
	return (res);
}
