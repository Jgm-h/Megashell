/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:27:44 by albaud            #+#    #+#             */
/*   Updated: 2023/12/31 04:01:54 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*jointo(char **join, size_t to, char glue)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = 0;
	while (join[++i] && i < to)
		len += strlen(join[i]);
	res = calloc(len + 1 + i, 1);
	i = -1;
	while (join[++i] && i < to)
	{
		strcat(res, join[i]);
		if (join[i + 1] && glue)
			strncat(res, &glue, 1);
	}
	return (res);
}

char	**str_to_strs(char *str)
{
	char	**res;

	res = calloc(2, 8);
	res[0] = str;
	return (res);
}

char	**strs_join(char **a, char **b, int to_free)
{
	int		i;
	int		len;
	char	**res;

	len = 0;
	i = -1;
	while (a[++i])
		len++;
	i = -1;
	while (b[++i])
		len++;
	res = calloc(len + 1, 8);
	len = -1;
	i = -1;
	while (a[++i])
		res[++len] = a[i];
	i = -1;
	while (b[++i])
		res[++len] = b[i];
	free(((void *[]){0, a, b})[to_free]);
	return (res);
}

char	*str_join(char *a, char *b, int to_free)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	i = -1;
	while (a[++i])
		len++;
	i = -1;
	while (b[++i])
		len++;
	res = calloc(len + 1, 1);
	len = -1;
	i = -1;
	while (a[++i])
		res[++len] = a[i];
	i = -1;
	while (b[++i])
		res[++len] = b[i];
	free(((char *[]){0, a, b})[to_free]);
	return (res);
}

char **strs_insert(char **a, char **b, int index)
{
	int		i;
	int		j;
	int		len;
	char	**res;

	len = 0;
	i = -1;
	while (a[++i])
		len++;
	i = -1;
	while (b[++i])
		len++;
	res = calloc(len + 1, 8);
	len = -1;
	i = -1;
	while (++i < index)
		res[++len] = a[i];
	j = -1;
	while (b[++j])
		res[++len] = b[j];
	i--;
	while (a[++i])
		res[++len] = a[i];
	return (res);
}