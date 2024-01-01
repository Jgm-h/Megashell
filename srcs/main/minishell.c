#include "minishell.h"
#include "builtins.h"

volatile extern int	g_status;

void	input_handling(t_container *book, char **input)
{
	*input = readline(book->prompt);
	add_history(*input);
}

int	minishell(t_container *book)
{
	char	*input;

	while (book)
	{
		g_status = NEW_LINE;
		book->in_pipe = FALSE;
		input_handling(book, &input);
		if (!input)
			break ;
		if (!lexer(&input))
			continue ;
		book->head = parser(input);
		if (!book->head)
			continue ;
		lexer_token(book->head, book);
		free(input);
		exec(book);
		free_leaf(book->head);
	}
	my_exit(NULL, book);
	return (1);
}
