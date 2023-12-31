# include "minishell.h"

T_BOOL	update_old_new_pwd(t_container *book)
{
	int	index;

	index = get_index_env(book->envp, "OLDPWD=");
	if (index == -1)
		add_var(book, ft_strdup("OLDPWD="), book->cwd);
	else
		export_value(&book->envp[index], ft_strdup("OLDPWD="), book->cwd);
	book->cwd = getcwd(NULL, 0);
	if (!book->cwd)
	{
		ft_putstr_fd("minishell-2.0: cwd", 2);
		return (FALSE);
	}
	index = get_index_env(book->envp, "PWD=");
	if (index == -1)
		add_var(book, ft_strdup("PWD="), ft_strdup(book->cwd));
	else
		export_value(&book->envp[index], \
		ft_strdup("PWD="), ft_strdup(book->cwd));
	return (TRUE);
}

int	handle_oldpwd(t_container *book)
{
	int		index;

	index = get_index_env(book->envp, "OLDPWD=");
	if (index == -1)
	{
		ft_putstr_fd("minishell-2.0: cd: OLDPWD not set", 2);
		errno = 1;
		return (ERROR);
	}
	if (chdir(book->envp[index] + 7) == -1)
	{
		ft_putstr_fd("minishell-2.0: cd: ",2 );
		ft_putstr_fd(book->envp[index] + 7, 2);
		ft_putstr_fd(": No such file or directory", 2);
		errno = 1;
		return (ERROR);
	}
	if (!update_old_new_pwd(book))
		return (ERROR);
	printf("%s", book->cwd);
	return (SUCCESS);
}

int	go_home(t_container *book)
{
	int		index;

	index = get_index_env(book->envp, "HOME=");
	if (index == -1)
	{
		ft_putstr_fd("minishell-2.0: cd: HOME not set", 2);
		return (ERROR);
	}
	if (chdir(book->envp[index] + 5) == -1)
		return (ERROR);
	if (!update_old_new_pwd(book))
		return (ERROR);
	return (SUCCESS);
}

int	normal_usage(t_token *leaf, t_container *book)
{
	if (chdir(leaf->args[1]) == -1)
	{
		ft_putstr_fd("minishell-2.0: cd: ", 2);
		ft_putstr_fd(leaf->args[1], 2);
		ft_putstr_fd(": No such file or directory", 2);
		return (ERROR);
	}
	if (!update_old_new_pwd(book))
		return (ERROR);
	errno = 0;
	return (SUCCESS);
}

T_BOOL	cd(t_token *leaf, t_container *book)
{
	if (book->in_pipe)
		return (SUCCESS);
	if (leaf->args[1][0] == '-' && !leaf->args[1][1])
		return (handle_oldpwd(book));
	if (leaf->args[1][0] == '-' && leaf->args[1][1])
	{
		ft_putstr_fd("minishell-2.0: cd:", 2);
		ft_putstr_fd(leaf->args[1], 2);
		ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]", 2);
		errno = 1;
		return (ERROR);
	}
	if (!leaf->args[1])
		return (go_home(book));
	return (normal_usage(leaf, book));
}
