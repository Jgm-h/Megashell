/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:46:46 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:46:47 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_leaf(t_token *leaf)
{
	if (!leaf)
		return ;
	if (leaf->left)
		free_leaf(leaf->left);
	if (leaf->right)
		free_leaf(leaf->right);
	if (leaf->args)
		free_array(leaf->args);
	if (leaf->argv)
	{
		leaf->argv = NULL;
		free(leaf->argv);
	}
	leaf = NULL;
	free(leaf);
}

void	free_all(t_container *book)
{
	if (book->head)
		free_leaf(book->head);
	if (book->envp)
		free_array(book->envp);
	if (book->paths)
		free_array(book->paths);
	if (book->prompt)
	{
		book->prompt = NULL;
		free(book->prompt);
	}
	if (book->cwd)
	{
		book->cwd = NULL;
		free(book->cwd);
	}
	if (book)
	{
		book = NULL;
		free(book);
	}
	rl_clear_history();
}
