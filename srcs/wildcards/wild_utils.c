/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:49:47 by albaud            #+#    #+#             */
/*   Updated: 2023/12/27 15:18:42 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/wildcard.h"
#include <sys/errno.h>

int	isdir(char *file)
{
	DIR		*dir;

	errno = 0;
	dir = opendir(file);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

char	**ft_split_deg(char *str, char c)
{
	char			*d;
	char			**r;
	const size_t	i[9] = (const size_t []){-1, -1, -1, 0, -1, -1, -1, -1, -1};

	while (str && str[++((size_t *)i)[1]] && ((i[6] && ((str[i[1]] == c &&
		++((size_t *)i)[7] < (size_t)-1) || ++((size_t *)i)[6])) || 1))
		;
	d = malloc((i[1] - (i[7] + 1) + (str != 0)));
	if (d == 0)
		return (0);
	while (++((size_t *)i)[0] < i[1] - i[7])
		d[i[0]] = 0;
	while (++((size_t *)i)[8] < (size_t)-1 && str[++((size_t *)i)[7]])
		if (str[i[7]] != c || (i[8] && d[i[8] - 1] && ++((size_t *)i)[3] > -1))
			d[i[8]] = str[i[7]];
	r = malloc(((i[3] + 2 - (d[i[8] - (i[8] != 0)] == 0)) * 8));
	free((void *)((long long)d * (r == 0)));
	if (r == 0)
		return (0);
	while ((long long)++((size_t *)i)[4] < (long long)(i[8]))
		if ((i[4] == 0 && d[i[4]] != 0) || (d[i[4] + 1] != 0 && d[i[4]] == 0))
			r[++((size_t *)i)[5]] = &d[i[4] + !(i[4] == 0 && d[i[4]] != 0)];
	r[++((size_t *)i)[5]] = 0;
	return (r);
}

int	free_split_degeu(char **split)
{
	free(split[0]);
	free(split);
	return (1);
}

char	**strsort(char **strs)
{
	int		f;
	int		i;
	char	*tmp;

	f = 1;
	while (f)
	{
		f = 0;
		i = -1;
		while (strs[++i] && strs[i + 1])
		{
			if (strcmp(strs[i], strs[i + 1]) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[i + 1];
				strs[i + 1] = tmp;
				f = 1;
			}
		}
	}
	return (strs);
}
