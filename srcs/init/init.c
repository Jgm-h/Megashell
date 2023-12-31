#include "minishell.h"
#include "init.h"

T_BOOL	print_error_init(char *str)
{
	ft_putstr_fd(str, 2);
	return (FALSE);
}

void init_nmbrs(t_container **book)
{
	(*book)->eof_sig = FALSE;
	(*book)->exit_status = 0;
	(*book)->in_pipe = FALSE;
	(*book)->nmbr_exec = 0;
}

unsigned int init(t_container **book, char **envp, int argc)
{
	if (argc != 1)
		return (print_error_init("Usage: ./minishell {don't use any arguments}\n"));
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (print_error_init("./minishell error with stream\n"));
	(*book) = ft_calloc(1, sizeof (t_container));
	if (!(*book))
		return (print_error_init("minishell-2.0: malloc error"));
	(*book)->exit_status = 0;
	(*book)->prompt = "minishell-2.0$";
	(*book)->cwd = getcwd(NULL, 0);
	if (!(*book)->cwd)
		return (print_error_init("minishell: getcwd: "));
	if (!init_envp(*book, envp) || !init_paths(*book))
		return (1);
	(*book)->prompt = ft_strdup("minishell-2.0$");
	if (!(*book)->prompt)
		return (print_error_init("minishell-2.0: malloc error"));
	init_termios();
	init_nmbrs(book);
	return (1);
}

void	init_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		ft_putstr_fd("tcgetattr", 2);
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		ft_putstr_fd("tcsetattr", 2);
		return ;
	}
}

unsigned int	init_paths(t_container *book)
{
	int		i;

	i = 0;
	while (ft_strncmp(book->envp[i], "PATH", 4))
		i++;
	book->paths = ft_split(book->envp[i] + 5, ':');
	if (!book->paths)
		return (FALSE);
	i = 0;
	while (book->paths[i])
	{
		book->paths[i] = ft_strjoin(ft_strdup(book->paths[i]), ft_strdup("/"));
		i++;
	}
	return (TRUE);
}

unsigned int	init_envp(t_container *book, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	book->envp = ft_calloc(i, sizeof (char *));
	if (!book->envp)
		return (FALSE);
	i = 0;
	while (envp[i])
	{
		book->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	book->envp[i] = NULL;
	return (TRUE);
}
