#include "minishell.h"

int skip_till_redir(char *str, T_BOOL cmd)
{
	int	i;
	T_BOOL in_double;
	T_BOOL in_single;

	i = 0;
	in_single = FALSE;
	in_double = FALSE;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '&') && (!in_double || !in_single))
			cmd = FALSE;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else if ((str[i] == '<' || str[i] == '>') && cmd)
			while (ft_isalnum(str[i]))
				i++;
		else if (ft_isalnum(str[i]))
			cmd = TRUE;
		else if ((str[i] == '<' || str[i] == '>') && !cmd && !in_single && !in_double)
			break;
		i++;
	}
	if (!str[i])
		return (-1);
	if (i == 0)
		return (0);
	return (i - 1);
}

char	*split_till_redir(char *input, int i)
{
	char	*ret;
	int		j;

	j = 0;
	if (i == 0)
		return (NULL);
	ret = ft_calloc(i + 1, sizeof (char));
	while (j <= i)
	{
		ret[j] = input[j];
		j++;
	}
	return (ret);
}

char	*split_redir(char *input, int *i)
{
	int		j;
	int		ind;
	char	*ret;

	j = (*i);
	ind = 0;
	if (!input[*i])
		return (NULL);
	while(input[(*i)] && input[(*i)] != '\'' && input[(*i)] != '\"' && !(input[(*i)] == ' ' && ft_isalpha(input[(*i) + 1])))
		(*i)++;
	ret = ft_calloc((*i) - j + 1, sizeof (char));
	while (j < (*i))
		ret[ind++] = input[j++];
	return (ret);
}

int		get_len(char *str, T_BOOL in_double, T_BOOL in_single)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '&') && (!in_double || !in_single))
			break ;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (ft_isalnum(str[i]))
			while (ft_isalnum(str[i]))
				i++;
		i++;
	}
	return (i);
}

char	*split_cmd(char *input, int *i)
{
	int		j;
	int		ind;
	char	*ret;

	ind = 0;
	if (!input[*i])
		return (NULL);
	j = get_len(&input[*i], FALSE, FALSE);
	ret = ft_calloc(get_len(&input[*i], FALSE, FALSE), sizeof(char));
	j += (*i);
	while (*i <= j)
		ret[ind++] = input[(*i)++];
	return (ret);
}

char	*split_end(char *input, int i)
{
	int	j;
	char	*ret;

	j = i;
	if (!input[i])
		return (NULL);
	while (input[j])
		j++;
	ret = ft_calloc(j - i + 1, sizeof (char));
	j = 0;
	while (input[i])
		ret[j++] = input [i++];
	return (ret);
}

void ft_reassemble(char ***split)
{
	(*split)[0] = ft_strjoin((*split)[0], (*split)[2]);
	(*split)[0] = ft_strjoin((*split)[0], (*split)[1]);
	(*split)[0] = ft_strjoin((*split)[0], (*split)[3]);
}

T_BOOL	lexer_redir_clean(char **input)
{
	int	i;
	char **split;

	i = 0;
	split = ft_calloc(5, sizeof(char *));
	while ((*input)[i])
	{
		i = skip_till_redir((*input), FALSE);
		if (i == -1)
		{
			free_array(split);
			break ;
		}
		split[0] = split_till_redir((*input), i);
		split[1] = split_redir((*input), &i);
		split[2] = split_cmd((*input), &i);
		split[3] = split_end((*input), i);
		ft_reassemble(&split);
		free((*input));
		(*input) =  split[0];
	}
	return (TRUE);
}

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
			tmp = ft_value_expand(&(*input)[i + 1], \
				book->envp, book->exit_status);
			if (!expand(input, book, i))
				return (FALSE);
			i += tmp;
		}
		else
			i++;
	}
	return (TRUE);
}

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

int ft_small_split(char *str, char **to_copy)
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
			break;
		else if (check && str[i] == c && c != ' ')
			check = !check;
		else if (!check && str[i] == c && c != ' ')
		{
			(*to_copy)[i] = str[i];
			i++;
			break;
		}
		(*to_copy)[i] = str[i];
		i++;
	}
	return (i);
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
		i += ft_small_split(&input[i], &(leaf->args[j]));
		j++;
	}
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
	if (leaf->type == COMMAND || leaf->type == IN_REDIR || leaf->type == OUT_REDIR || leaf->type == HEREDOC || leaf->type == APD_REDIR)
	{
		split_var(leaf->argv, leaf);
		while (leaf->args[i])
		{
			if (!expand_variables(&(leaf->args[i]), book))
				return (FALSE);
			clean_quotes(&(leaf->args[i++]), 0, 0, 0);
			clean_quotes(&(leaf->argv), 0, 0, 0);
		}
		return (TRUE);
	}
	return (FALSE);
}
