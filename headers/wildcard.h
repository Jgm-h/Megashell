/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:49:59 by albaud            #+#    #+#             */
/*   Updated: 2023/12/27 15:18:30 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

char	**strsort(char **strs);
char	**str_to_strs(char *str);
char	*jointo(char **join, size_t to, char glue);
char	**strs_join(char **a, char **b, int to_free);
char	*str_join(char *a, char *b, int to_free);
char	**ft_split_deg(char *str, char c);
char	**strs_insert(char **a, char **b, int index);

char	*jointo(char **join, size_t to, char glue);
int		isdir(char *file);
int		cmpto(char *a, char *b, char to);
int		wildcmp(char *a, char *b, char wildchar);
int		isdir(char *file);
int		free_split_degeu(char **split);

void	wildcard_at_loop(char **strs, char **srcdest, DIR *d, int dironly);
char	**wildcard_at(char *dirname, char *str, int dironly);
char	**wildcard_collapse(char **files, char **split, int index);
char	**wildcard_multi_dir(char *str);
char	**wildcard(char *str);

#endif