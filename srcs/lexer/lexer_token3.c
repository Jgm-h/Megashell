#include "minishell.h"

int	ft_redirlen(char *redir)
{
	int	i;

	i = 0;
	while (*redir && (*redir == '<' || *redir == '>'))
	{
		redir++;
		i++;
	}
	while (*redir && *redir != ' ' && *redir != '<' && *redir != '>' \
		&& *redir != ')' && *redir != '|' && *redir != '&')
	{
		redir++;
		i++;
	}
	return (i);
}

T_BOOL	check_heredoc_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!ft_strncmp(&input[i], (char *)"<<", 2))
	{
		while (input[i] != ' ' && input[i] != '(' && input[i] != ')')
			i++;
		if (input[i] == '(')
		{
			ft_putstr_fd("syntax error near unexpected token `('", 2);
			return (FALSE);
		}
		if (input[i] == ')')
		{
			ft_putstr_fd("syntax error near unexpected token `)'", 2);
			return (FALSE);
		}
		while (input[i] == ' ')
			i++;
		if (!input[i])
			return (FALSE);
	}
	return (TRUE);
}

T_BOOL	check_heredoc_alone(char *input, int i, T_BOOL first)
{
	while (input[i] && input[i] == ' ')
		i++;
	if (!check_heredoc_start(input))
		return (FALSE);
	while (input[i])
	{
		if (!ft_strncmp(&input[i], "<<", 2))
		{
			if (first)
			{
				ft_putstr_fd("syntax error near unexpected token '<<'", 2);
				return (FALSE);
			}
			if (!input[i + 2])
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
				return (FALSE);
			}
			first = TRUE;
		}
		i++;
	}
	return (TRUE);
}
