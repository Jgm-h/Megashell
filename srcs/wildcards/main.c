/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 19:26:25 by albaud            #+#    #+#             */
/*   Updated: 2023/12/27 15:19:23 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	char	**res;
	int		i;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	res = wildcard(argv[1]);
	i = -1;
	while (res[++i])
	{
		if (res[i + 1])
			printf("%s ", res[i]);
		else
			printf("%s\n", res[i]);
	}
	return (0);
}
