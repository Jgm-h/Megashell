#ifndef LEXER_H
#define LEXER_H
# include "minishell.h"

T_BOOL			check_closed_quotes(const char *input, \
				int in_single, int in_double);
T_BOOL			expand_variables(char **input, t_container *book);
T_BOOL			check_state(char *input, int pos, \
				T_BOOL in_double, T_BOOL in_simple);
T_BOOL			check_expand(char *input, int i, t_container *book);
unsigned int	expand(char **input, t_container *book, int i);
unsigned int	ft_expand_exit(char **input, int i, t_container *book);
int				ft_strcmp_lexer(const char *s1, const char *s2);
unsigned int	ft_strcpy_lexer(char **input, int i, char *env, int j);
int				ft_value_expand(char *input, char **envp, int exit_status);
int				ft_keysize(char *envp);
int				ft_intlen(int number);
int				ft_keysize_input(char *s1);
void			c_qts(char **input, T_BOOL in_double, T_BOOL in_simple, int i);
T_BOOL			check_heredoc_alone(char *input, int i, T_BOOL first);
T_BOOL			check_heredoc_start(char *input);
char			**wildcardmoicasalpouilleudesclave(char **args, int i);
char			find_sep(char *str);
int				get_len_split(char *str);
void			alloc(char *input, t_token *leaf, T_BOOL simp, T_BOOL doub);
void			split_var(char *input, t_token *leaf);

#endif //LEXER_H
