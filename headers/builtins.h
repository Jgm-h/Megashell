/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:38:29 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:41:15 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		pwd(void);
T_BOOL	echo(t_token *leaf, t_pipes pipes);
T_BOOL	cd(t_token *leaf, t_container *book);
int		env(t_token *leaf, t_container *book);
void	my_exit(t_token *leaf, t_container *book);
T_BOOL	export(t_token *leaf, t_container *book);
T_BOOL	unset(t_token *leaf, t_container *book);

#endif //BUILTINS_H
