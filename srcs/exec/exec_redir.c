#include "exec.h"

volatile extern int	g_status;

int	get_redir_fd_side(char *file, enum e_token_type type)
{
	int	fd;

	if (type == IN_REDIR)
	{
		if (!my_access(file, R_OK))
			return (-1);
		fd = open(file, O_RDONLY);
	}
	if (type == OUT_REDIR || type == APD_REDIR)
	{
		if (!my_access(file, W_OK))
			return (-1);
		fd = open(file, O_WRONLY);
	}
	if (fd == -1)
		ft_putstr_fd("minishell-2.0: open failed", 2);
	return (fd);
}

T_BOOL	get_heredoc(t_token *leaf, t_container *book)
{
	book->eof = leaf->argv;
	book->eof_sig = TRUE;
	pipe(book->pipe_here);
	return (TRUE);
}

unsigned int	one_redir(t_token *leaf, char *file, \
	t_pipes pipes, t_container *book)
{
	int		fd_file;

	if (leaf->type != HERDOC)
	{
		fd_file = get_redir_fd_side(file, leaf->type);
		if (fd_file == -1)
			return (FALSE);
	}
	else
		return (get_heredoc(leaf, book));
	if (leaf->type == OUT_REDIR || leaf->type == APD_REDIR)
	{
		if (my_dup2(fd_file, pipes.out) == -1)
			return (FALSE);
	}
	if (leaf->type == IN_REDIR)
	{
		if (my_dup2(fd_file, pipes.in) == -1)
			return (FALSE);
	}
	close(fd_file);
	return (TRUE);
}

T_BOOL	redir_management(t_token *leaf, t_pipes pipes, t_container *book)
{
	while (leaf && leaf->type != COMMAND)
	{
		if (!one_redir(leaf, leaf->argv, pipes, book))
			return (FALSE);
		leaf = leaf->right;
	}
	return (TRUE);
}

T_BOOL	execute_redir(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (!redir_management(leaf, pipes, book))
	{
		book->exit_status = errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(leaf->argv, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
