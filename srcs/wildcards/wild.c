/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:08:25 by albaud            #+#    #+#             */
/*   Updated: 2023/12/27 15:19:02 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/wildcard.h"

//search for matching file 
void	wildcard_at_loop(char **strs, char **srcdest, DIR *d, int dironly)
{
	struct dirent	*dir;
	char			buffer[2048];
	int				len;

	dir = readdir(d);
	strcpy(buffer, srcdest[0]);
	len = strlen(buffer);
	while (dir != NULL)
	{
		strcat(buffer, dir->d_name);
		if (dir->d_name[0] != '.' && (!dironly || isdir(buffer))
			&& !wildcmp(srcdest[1], dir->d_name, 1))
			*(strs++) = str_join(buffer, ((char *[]){"", "/"})[dironly], 0);
		buffer[len] = 0;
		dir = readdir(d);
	}
}

// return the list of file at dirname marching str
char	**wildcard_at(char *dirname, char *str, int dironly)
{
	DIR				*d;
	char			**res;
	int				len;

	len = strlen(dirname);
	d = opendir(dirname);
	if (!d)
		return (0);
	res = calloc(d->__dd_len + 1, 8);
	if (res == 0)
		return (0);
	wildcard_at_loop(res, (char *[]){dirname, str}, d, dironly);
	closedir(d);
	return (res);
}

// search for all the direcory sub file 
char	**wildcard_collapse(char **files, char **split, int index)
{
	int		i;
	char	*chr;
	char	**res;
	char	**tmp;

	i = -1;
	res = calloc(1, 8);
	while (files[++i])
	{
		if (!isdir(files[i]))
			continue ;
		split[index] = files[i];
		chr = jointo(&split[index], -1, '/');
		tmp = wildcard_multi_dir(chr);
		res = strs_join(res, tmp, 1);
	}
	return (res);
}

char	**wildcard_multi_dir(char *str)
{
	char	**split;
	char	**res;
	int		i;
	char	*debut;

	split = ft_split_deg(str, '/');
	i = -1;
	while (split[++i] && strchr(split[i], 1) == 0)
		;
	if (split[i] == 0 && free_split_degeu(split))
		return (str_to_strs(str));
	if (i == 0)
		debut = ((char *[]){"./", "/"})[str[0] == '/'];
	else
		debut = str_join(((char *[]){"", "/"})[str[0] == '/'],
				jointo(split, i, '/'), 2);
	res = wildcard_at(debut, split[i], str[strlen(str) - 1] == '/');
	if (split[i + 1] != 0)
		res = wildcard_collapse(res, split, i);
	free_split_degeu(split);
	free((void *)(((long long)debut) * (i != 0)));
	return (res);
}

// return a list of filename that matches str the wildcard way
char	**wildcard(char *str)
{
	char	**res;

	res = wildcard_multi_dir(str);
	res = strsort(res);
	return (res);
}
