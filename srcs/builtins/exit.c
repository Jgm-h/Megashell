/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:45:11 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:45:14 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_BOOL	check_nmbr_args(t_token *leaf)
{
	int	i;

	i = 0;
	while (leaf->args[i])
		i++;
	if (i > 2)
		return (TRUE);
	return (FALSE);
}

int	check_digit(t_token *leaf)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!leaf || !leaf->args[1])
		return (0);
	while (leaf->args[i])
	{
		if (leaf->args[1][j] == '+' || leaf->args[1][j] == '-')
			j++;
		while (leaf->args[1][j] && ft_isdigit(leaf->args[1][j]))
			j++;
		if (leaf->args[1][j] && !ft_isdigit(leaf->args[1][j]))
		{
			ft_putstr_fd("minishell-2.0: exit:", 2);
			ft_putstr_fd(leaf->args[1], 2);
			ft_putstr_fd(" numeric argument required", 2);
		}
		i++;
	}
	return (i - 1);
}

void	my_exit(t_token *leaf, t_container *book)
{
	int	tmp;

	if (!leaf)
	{
		free_all(book);
		ft_putstr_fd("minishell-2.0: exit", 2);
		exit(0);
	}
	if (leaf && (book->in_pipe || check_nmbr_args(leaf)))
	{
		errno = 1;
		if (check_nmbr_args(leaf))
			ft_putstr_fd("exit\nminishell-2.0: exit: too many arguments", 2);
		return ;
	}
	ft_putstr_fd("exit", 2);
	tmp = check_digit(leaf);
	if (tmp == 1)
		tmp = ft_atoi(leaf->args[1]);
	free_all(book);
	if (!tmp)
		exit(255);
	exit((unsigned char) tmp);
}
