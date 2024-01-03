/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:40:45 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:43:01 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# include "stdio.h"
# include <errno.h>
# include "signal.h"
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

enum e_token_type{
	AND,
	OR,
	PIPE,
	HERDOC,
	APD_REDIR,
	IN_REDIR,
	OUT_REDIR,
	COMMAND,
};

enum e_status{
	NEW_LINE,
	EXECUTION,
	HEREDOC,
	ABORT_HEREDOC
};

typedef struct s_pipes
{
	int	in;
	int	out;
}	t_pipes;

typedef struct s_token
{
	enum e_token_type	type;
	char				*argv;
	char				**args;
	struct s_token		*left;
	struct s_token		*right;
}	t_token;

typedef struct s_container{
	T_BOOL	eof_sig;
	int		o_fdin;
	int		o_fdout;
	int		exit_status;
	T_BOOL	in_pipe;
	int		nmbr_exec;
	char	*eof;
	int		*pipe_here;
	t_token	*head;
	char	**envp;
	char	**paths;
	char	*prompt;
	char	*cwd;
}t_container;

int		get_index_env(char **envp, char *key);
void	add_var(t_container *book, char *key, char *value);
void	free_split(char **to_free);
int		fork1(void);
void	manage_heredoc(t_container *book);
int		my_dup2(int fd_file, int to_dup);
void	restore_fds(t_container *book, t_pipes pipe);
T_BOOL	my_access(char *file, int flag);
void	export_value(char **env, char *key, char *value);

int		check_builtin(char *str);
void	free_array(char **array);
void	free_leaf(t_token *leaf);
T_BOOL	check_empty_prompt(char *input);
T_BOOL	execute_builtins(t_token *leaf, \
				t_container *book, t_pipes pipes);
void	free_all(t_container *book);
void	write_heredoc(t_container *book, char *input, char *to_send);

#endif //UTILS_H
