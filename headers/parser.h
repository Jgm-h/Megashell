#ifndef PARSER_H
#define PARSER_H
# include "minishell.h"

char	*parenthese_trim(char *prompt);
char	*trim_space(char *prompt);
int		find_level(char *prompt, int level);
t_token	*get_redir(char *prompt, int i, char *redire_type);
t_token	*redir(char *prompt, int i, t_token *res, t_token *tmp);
int		iswhitespace(char c);
int		skip_quotes(char *prompt, int i);
int		print_syntax_error(char *message);

#endif //PARSER_H
