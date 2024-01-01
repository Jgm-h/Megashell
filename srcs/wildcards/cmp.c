/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:07:42 by albaud            #+#    #+#             */
/*   Updated: 2023/12/25 01:29:29 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/wildcard.h"

int	cmpto(char *a, char *b, char to)
{
	while (*(a) && *(b) && *(a) == *(b))
	{
		a++;
		b++;
	}
	return ((*a == to || (*a - *b == 0)));
}

char	*last_index(char *a, char *b, char wildchar)
{
	int		index;
	char	*res;

	res = 0;
	while (*b)
	{
		index = cmpto(a, b, wildchar);
		if (index)
			res = b;
		b++;
	}
	return (res);
}

int	wildcmp(char *a, char *b, char wildchar)
{
	char	*ind;

	while (*a && *b)
	{
		if (*a != wildchar)
		{
			if (*b != *a)
				return (1);
			a++;
			b++;
			continue ;
		}
		while (*a == wildchar)
			a++;
		if (*a == 0)
			return (0);
		ind = last_index(a, b, wildchar);
		if (ind == 0)
			return (1);
		b = ind;
	}
	while (*a == wildchar)
		a++;
	return (*a - *b);
}
