/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:38:49 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:41:32 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
# include "minishell.h"

unsigned int	init_envp(t_container *book, char **envp);
unsigned int	init_paths(t_container *book);
void			init_termios(void);
void			init_nmbrs(t_container *book);

#endif //INIT_H
