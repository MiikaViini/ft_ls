/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/16 15:19:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Count files in directory
*/
static int filecount(char *dir)
{
	DIR 			*dir_s;
	struct dirent	*entity;
	int				count;

	count = 0;
	dir_s = opendir(dir);
	if (dir_s == NULL)
	{
		print_err(dir, errno);
		return (0);
	}
	entity = readdir(dir_s);
	while (entity != NULL)
	{
		count++;
		entity = readdir(dir_s);
	}
	closedir(dir_s);
	return (count);
}
/*
** Make path for opendir function
*/
void	path_maker(char *dest, char *dirname)
{
	int	i;

	i = -1;
	ft_memset(dest, '\0', ft_strlen(dirname) + 2);
	while (dirname[++i])
		dest[i] = dirname[i];
	if (dest[i] != '/')
		dest[i++] = '/';
	dest[i] = '\0';
}
/*
** This is for -R flag only, go through directories recursively
*/
void recursively(char *dirname, t_fileinfo **linearray, t_flags *flags)
{
	t_fileinfo		**arr;
	char			path[PATH_MAX];
	int				f_count;
	int				i;

	i = -1;
	f_count = filecount(dirname);
	if (f_count <= 0)
		return ;
	arr = ft_opendir(dirname, linearray, flags, f_count);
	if (!arr)
		return ;
	print_arr(sort_handler(arr, flags), flags);
	while (arr[++i])
	{
		if (arr[i]->perms[0] == 'd' && ft_strcmp(arr[i]->filename, ".") != 0 && ft_strcmp(arr[i]->filename, "..") != 0)
		{
			path_maker(path, dirname);
			ft_strcat(path, arr[i]->filename);
			ft_printf("\n%s:\n", path);
			recursively(path, arr, flags);
		}
	}
	free_linearray(arr);
}

t_fileinfo **save_info(char *path, char *dirname, t_fileinfo **linearray, t_flags *flags)
{
	DIR				*dirp;
	struct dirent	*entity;
	struct stat		buf;
	int				i;

	i = 0;
	flags->blocks= 0;
	dirp = opendir(dirname);
	entity = readdir(dirp);
	if (ft_strcmp(dirname, "/") == 0)
		ft_memset(dirname, '\0', ft_strlen(dirname));
	while (entity != NULL)
	{
		dirname = ft_strjoin(path, entity->d_name);
		lstat(dirname, &buf);							//
		if (entity->d_name[0] != '.' || flags->a || flags->f)
			linearray[i++] = get_info(buf, dirname, ft_strlen(path));
		flags->blocks += buf.st_blocks;
		entity = readdir(dirp);
		ft_strdel(&dirname);
	}
	linearray[i] = NULL;
	closedir(dirp);
	return (linearray);
}

t_fileinfo	**ft_opendir(char *dirname, t_fileinfo **linearray, t_flags *flags, int f_count)
{
	char			path[PATH_MAX];

	f_count = filecount(dirname);
	if (f_count <= 0)
		return (NULL);
	path_maker(path, dirname);
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * f_count + 2);
	if (!linearray)
		return (NULL);
	linearray = save_info(path, dirname, linearray, flags);
	return (sort_handler(linearray, flags));
}
