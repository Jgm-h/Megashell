/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:40:28 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:42:32 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "utils.h"

t_container		*init(t_container *book, char **envp, int argc);
unsigned int	lexer(char **input);
t_token			*parser(char *prompt);
T_BOOL			lexer_token(t_token *leaf, t_container *book);
void			signal_handler(int signal);
int				minishell(t_container *book, char **envp, int argc);
void			exec(t_container *book);

#endif //MINISHELL_H
