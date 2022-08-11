/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/11 13:47:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// static void free_linearray(t_fileinfo **linearray)
// {
// 	int		i;

// 	i = -1;
// 	while (linearray[++i])
// 	{
// 		ft_strdel(&linearray[i]->m_time);
// 		ft_strdel(&linearray[i]->owner);
// 		ft_strdel(&linearray[i]->owner_gr);
// 		ft_strdel(&linearray[i]->perms);
// 	}
// }
// static int char_count(char *string, char c)
// {
// 	int	res;
// 	int	i;

// 	res = 0;
// 	i = -1;
// 	while (string[++i])
// 		if (string[i] == c)
// 			res++;
// 	return (res);
// }
// static void	save_dir_info(t_dirs **dirs, char *dirname, struct dirent *folder)
// {
// 	t_dirs 			*dir;
// 	static int 		i;
// 	struct stat		buf;

// 	dir = (t_dirs *)malloc(sizeof(t_dirs));
// 	dir->time = ft_strnew(30);
// 	if(!dir || !dirs || !folder)
// 		return ;
// 	lstat(dirname, &buf);
// 	dir->dirs = ft_strdup(dirname);
// 	dir->depth = char_count(dirname, '/');
// 	dir->time_i = buf.st_mtime;
// 	//ft_strncpy(dir->time, ctime(&buf.st_mtime) + 4, 12);
// 	if (!dir->dirs)
// 		return ;
// 	dirs[i++] = dir;
// }

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

void print_err(char *dirname, int error)
{
	// if (flags->cap_r)
	// 	{
	// if (error == EACCES)
	ft_printf("ft_ls: %s: %s \n",dirname, strerror(error));
	// else if (error == ENOTDIR)
	// 	ft_printf("ft_ls: %s: %s \n",dirname, strerror(ENOENT));
	// else if (error == ELOOP)
	// 	ft_printf("ft_ls: %s: %s \n",dirname, strerror(ELOOP));
 }

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
	free(arr);
}



t_fileinfo	**ft_opendir(char *dirname, t_fileinfo **linearray, t_flags *flags, int f_count)
{
	DIR				*dirp;
	struct dirent	*entity;
	struct stat		buf;
	int				i;
	char			path[PATH_MAX];

	i = 0;
	flags->blocks= 0;
	f_count = filecount(dirname);
	if (f_count <= 0)
		return (NULL);
	path_maker(path, dirname);
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * f_count + 1);
	dirp = opendir(dirname);
	entity = readdir(dirp);
	if (ft_strcmp(dirname, "/") == 0)
		ft_memset(dirname, '\0', ft_strlen(dirname));
	while (entity != NULL)
	{
		dirname = ft_strjoin(path, entity->d_name);
		lstat(dirname, &buf);
		if (entity->d_name[0] != '.' || flags->a)
			linearray[i++] = get_info(buf, dirname, ft_strlen(path));
		flags->blocks += buf.st_blocks;
		entity = readdir(dirp);
		ft_strdel(&dirname);
	}
	linearray[i] = NULL;
	closedir(dirp);
	print_arr(sort_handler(linearray, flags), flags);
	return (linearray);
}

// alphabetical(linearray);
	// if (flags->t)
	// {
	// 	sort_time_a(linearray);
	// 	sort_time(linearray);
	// }
	// 
// {
// 	DIR				*dp;
// 	struct dirent	*dirp;
// 	struct stat		buf;

// 	int				i;
// 	char			*temp;
// 	char			*path;
// 	temp = ft_strjoin(argv, "/");
// 	dp = opendir(temp);
// 	dirp = readdir(dp);
// 	i = 0;
// 	while (dirp != NULL)
// 	{
// 		path = ft_strjoin(temp, dirp->d_name);
// 		stat(path, &buf);
// 		linearray[i] = get_info(buf, path, ft_strlen(temp));
// 		linearray[0]->total += buf.st_blocks;
// 		i++;
// 		// if (dirp->d_type == DT_DIR && ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
// 		// {
// 		// 	//ft_printf("stuff from %s\n", argv);
// 		// 	path = ft_strnew(100);
// 		// 	path = ft_strjoin(temp, dirp->d_name);
// 		// 	line_array(path, index, linearray);
// 		// }
// 		dirp = readdir(dp);
// 	}
// 	linearray[i] = NULL;
// 	linearray = alphabetical(linearray);
// 	closedir(dp);
// 	return (linearray);
// }
