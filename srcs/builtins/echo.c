/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:43:38 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:43:41 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

T_BOOL	echo(t_token *leaf, t_pipes pipes)
{
	T_BOOL	option;
	int		i;

	i = 1;
	option = FALSE;
	if (!leaf->args[1])
	{
		ft_putstr_fd("\n", pipes.out);
		return (SUCCESS);
	}
	if (!ft_strncmp(leaf->args[1], "-n", 3))
	{
		option = TRUE;
		i++;
	}
	while (leaf->args[i])
		ft_putstr_fd(leaf->args[i++], pipes.out);
	if (option)
		return (SUCCESS);
	ft_putstr_fd("\n", pipes.out);
	errno = 0;
	return (SUCCESS);
}
