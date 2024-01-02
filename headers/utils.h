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
# include "minishell.h"

enum e_token_type{
	AND,
	OR,
	PIPE,
	HERDOC,
	IN_REDIR,
	APD_REDIR,
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
	t_token	*head;
	char	**envp;
	char	**paths;
	char	*prompt;
	char	*cwd;
	char	*eof;
	T_BOOL	eof_sig;
	int		*pipe_here;
	int		exit_status;
	T_BOOL	in_pipe;
	int		nmbr_exec;
}t_container;

int		get_index_env(char **envp, char *key);
void	add_var(t_container *book, char *key, char *value);
void	free_split(char **to_free);
int		fork1(void);
void	manage_heredoc(t_container *book);
int		my_dup2(int fd_file, int to_dup);
T_BOOL	my_access(char *file, int flag);
void	export_value(char **env, char *key, char *value);

int		check_builtin(char *str);
void	free_array(char **array);
void	free_leaf(t_token *leaf);

#endif //UTILS_H
