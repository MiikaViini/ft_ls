/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:30:25 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/12 10:06:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_filetype(struct stat buf)
{
	char	file_c;

	file_c = '-';
	if (S_ISDIR(buf.st_mode))
		file_c = 'd';
	else if (S_ISLNK(buf.st_mode))
		file_c = 'l';
	else if (S_ISFIFO(buf.st_mode))
		file_c = 'p';
	else if (S_ISCHR(buf.st_mode))
		file_c = 'c';
	else if (S_ISBLK(buf.st_mode))
		file_c = 'b';
	else if (S_ISSOCK(buf.st_mode))
		file_c = 's';
	else if (S_ISWHT(buf.st_mode))
		file_c = 'w';
	return (file_c);
}

static void get_stickybits(int modes, char *perm)
{
	if((modes & S_IXUSR) && (modes & S_ISUID))
		perm[3] = 's';
	else if (!(modes & S_IXUSR) && (modes & S_ISUID))
		perm[3] = 'S';
	if((modes & S_IXGRP) && (modes & S_ISGID))
		perm[6] = 's';
	else if (!(modes & S_IXGRP) && (modes & S_ISGID))
		perm[6] = 'S';
	if((modes & S_IXOTH) && (modes & S_ISVTX))
		perm[9] = 't';
	else if (!(modes & S_IXOTH) && (modes & S_ISVTX))
		perm[9] = 'T';
}

char	*permissions(int modes, struct stat buf)
{
	char	*perm;
	int		i;
	int		k;
	char	*mode;
	char	*temp;

	i = 0;
	k = 0;
	mode = ft_itoabase(modes, 8, 0);
	temp = ft_strdup(&mode[ft_strlen(mode) - 3]);
	perm = ft_strnew(11);
	if (!temp || !perm || !mode)
		return (NULL);
	perm[i] = get_filetype(buf);
	while (temp[k] && ++i)
		ft_strcat(&perm[i], g_perms[temp[k++] - '0']);
	get_stickybits(modes, perm);
	ft_strdel(&temp);
	ft_strdel(&mode);
	return (perm);
}
