/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorcom- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:47:19 by jmorcom-          #+#    #+#             */
/*   Updated: 2024/01/01 23:47:20 by jmorcom-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_nmbrs(t_container **book)
{
	(*book)->eof_sig = FALSE;
	(*book)->exit_status = 0;
	(*book)->in_pipe = FALSE;
	(*book)->nmbr_exec = 0;
}
