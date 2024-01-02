/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:38:36 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:41:26 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

int		exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes);
char	*find_path(t_container *book, int i, char *arg);
T_BOOL	execute_redir(t_token *leaf, t_container *book, t_pipes pipes);
T_BOOL	r_executor(t_token *leaf, t_container *book, t_pipes pipes);
T_BOOL	execute_pipe(t_token *leaf, t_container *book, t_pipes pipes);
void	execute(t_token *leaf, t_container *book, t_pipes pipes);
void	pipes_management(t_pipes pipes, t_container *book, t_token *leaf);
T_BOOL	path_error(t_token *leaf, t_container *book);
void	handle_exit_status(int status);

#endif //EXEC_H
