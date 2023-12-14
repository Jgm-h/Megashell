#include "minishell.h"
#include "lexer.h"

/*version one checks if there is an odd or even number of single and double quotes
 * tested with: "'" '"'
 * */
T_BOOL	check_closed_quotes(const char *input, int in_single, int in_double)
{
	int		single_quotes;
	int		double_quotes;
	int		i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !(in_double % 2))
		{
			in_single++;
			single_quotes++;
		}
		if (input[i] == '\"' && !(in_single % 2))
		{
			in_double++;
			double_quotes++;
		}
		i++;
	}
	if (single_quotes % 2 || double_quotes % 2)
		return (FALSE);
	return (TRUE);
}

/*
 * I want this to check if i can expand depending on quote status:
 * 	if i-m in double quotes, and then in single inside the dobule i still expand
 * 	if im single i don't expand
 * 	if im in none i expand
 *
 * if i can and i encounter a $:
 * if i can't expand what comes i delete it(the $ and what comes after) from the chain
 * */
T_BOOL	check_state(char *input, int pos, T_BOOL in_double, T_BOOL in_simple)
{
	int		i;
	T_BOOL	can_exp;

	i = 0;
	can_exp = TRUE;
	while (i <= pos)
	{
		if (input[i] == '\"' && !in_simple && !in_double)
			in_double = TRUE;
		else if (input[i] == '\"' && !in_simple && in_double)
			in_double = FALSE;
		if (input[i] == '\'' && !in_double && !in_simple)
		{
			in_simple = TRUE;
			can_exp = FALSE;
		}
		else if (input[i] == '\'' && !in_double && in_simple)
		{
			in_simple = FALSE;
			can_exp = TRUE;
		}
		i++;
	}
	return (can_exp);
}


T_BOOL	check_double(char *input, int pos, T_BOOL in_double, T_BOOL in_simple)
{
	int		i;

	i = 0;
	while (i <= pos)
	{
		if (input[i] == '\"' && !in_simple && !in_double)
			in_double = TRUE;
		else if (input[i] == '\"' && !in_simple && in_double)
			in_double = FALSE;
		if (input[i] == '\'' && !in_double && !in_simple)
			in_simple = TRUE;
		else if (input[i] == '\'' && !in_double && in_simple)
			in_simple = FALSE;
		i++;
	}
	return (in_double | in_simple);
}
/*CODE DE MERDE XD
 * */
T_BOOL	check_expand(char *input, int i, t_container *book)
{
	int	j;

	j = 0;
	if (input[i] == '$')
	{
		if (input[i + 1] == '?')
			return (TRUE);
		while (book->envp[j])
		{
			if (!ft_strcmp_lexer(&input[i + 1], (book->envp[j])))
				return (TRUE);
			j++;
		}
		return (TRUE);
	}
	return (FALSE);
}
