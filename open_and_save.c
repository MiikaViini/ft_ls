/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/28 16:42:26 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	filecount(char *dir)
{
	DIR				*dir_s;
	struct dirent	*entity;
	int				count;

	count = 0;
	dir_s = opendir(dir);
	if (dir_s == NULL)
		return (get_error(dir));
	entity = readdir(dir_s);
	while (entity != NULL)
	{
		count++;
		entity = readdir(dir_s);
	}
	closedir(dir_s);
	return (count);
}

void	recursively(char *dirname, t_fileinfo **linearray, t_info *flags)
{
	t_fileinfo		**arr;
	char			path[PATH_MAX];
	int				f_count;
	int				i;

	i = -1;
	f_count = filecount(dirname);
	if (f_count <= 0)
		return ;
	arr = open_dir(dirname, linearray, flags, f_count);
	if (!arr)
		return ;
	print_arr(sort_handler(arr, flags), flags);
	while (arr[++i])
	{
		if (arr[i]->perms[0] == 'd' && ft_strcmp(arr[i]->filename, ".") != 0
			&& ft_strcmp(arr[i]->filename, "..") != 0)
		{
			path_maker(path, dirname);
			ft_strcat(path, arr[i]->filename);
			ft_printf("\n%s:\n", path);
			recursively(path, arr, flags);
		}
	}
	free_linearray(arr);
}

int	entity_is_saveable(char *f_name, t_info *flags)
{
	int	res;

	res = 1;
	if (f_name[0] == '.')
	{
		res = 0;
		if (flags->cap_a)
		{
			if (ft_strcmp(f_name, ".") != 0 && ft_strcmp(f_name, "..") != 0)
				res = 1;
		}
		if ((flags->a && f_name[0] == '.') || (flags->f && f_name[0] == '.'))
			res = 1;
	}
	if (res == 1)
		flags->f_count++;
	return (res);
}

t_fileinfo	**save_info(char *path, char *dirname,
	t_fileinfo **linearray, t_info *info)
{
	DIR				*dirp;
	struct dirent	*entity;
	struct stat		buf;
	int				i;

	i = 0;
	info->blocks = 0;
	dirp = opendir(dirname);
	entity = readdir(dirp);
	if (ft_strcmp(dirname, "/") == 0)
		ft_memset(dirname, '\0', ft_strlen(dirname));
	while (entity != NULL)
	{
		dirname = ft_strjoin(path, entity->d_name);
		lstat(dirname, &buf);
		if (entity_is_saveable(entity->d_name, info) == 1)
			linearray[i++] = get_info(buf, dirname, ft_strlen(path), info);
		entity = readdir(dirp);
		ft_strdel(&dirname);
	}
	linearray[i] = NULL;
	closedir(dirp);
	return (linearray);
}

t_fileinfo	**open_dir(char *dirname, t_fileinfo **linearray,
				t_info *flags, int f_count)
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
