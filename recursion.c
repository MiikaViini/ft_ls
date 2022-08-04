/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/04 20:05:00 by mviinika         ###   ########.fr       */
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
// 		ft_strdel(&linearray[i]->filename);
// 		ft_strdel(&linearray[i]->perms);
// 		//free(linearray[i]);
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

int filecount(char *dir)
{
	DIR 			*dir_s;
	struct dirent	*entity;
	int				count;

	count = 0;
	dir_s = opendir(dir);
	if (dir_s == NULL)
	// {
	// 	ft_printf("ls: %s: %s\n",dir,strerror(EACCES));
		return (0);
	// }

	entity = readdir(dir_s);
	while (entity != NULL)
	{
		count++;
		entity = readdir(dir_s);
	}
	closedir(dir_s);
	return (count);
}


void recursively(char *dirname, t_fileinfo **linearray, t_flags *flags)
{
	t_fileinfo		**arr;
	char			path[PATH_MAX];
	int				f_count;
	int				i;

	i = 0;
	f_count = filecount(dirname);
	// if (f_count <= 0)
	// 	return ;
	arr = ft_opendir(dirname, linearray, flags, f_count);
	while (arr[i])
	{
		if (arr[i]->perms[0] == 'd' && ft_strcmp(arr[i]->filename, ".") != 0 && ft_strcmp(arr[i]->filename, "..") != 0)
		{
			ft_memset(path, '\0', PATH_MAX);
			ft_strcat(path, dirname);
			if (ft_strcmp(dirname, "/"))
				ft_strcat(path, "/");
			ft_strcat(path,arr[i]->filename);
			write(1, "\n", 1);
			write(1, path, ft_strlen(path));
			write(1, ":\n", 2);
			recursively(path, arr, flags);
		}
		i++;
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
	f_count = filecount(dirname);
	ft_memset(path, '\0', PATH_MAX);
	ft_strcat(path, dirname);
	ft_strcat(path, "/");
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * f_count + 1);
	if (!linearray)
		return (NULL);
	dirp = opendir(dirname);
	if (dirp == NULL)
	{
		ft_printf("ls: %s: %s ",dirname, strerror(EACCES));
		if (flags->cap_r)
		{
			write(1, "\n", 1);
			write(1, path, ft_strlen(path));
			write(1, ":\n", 2);
		}
		return (NULL);
	}
	entity = readdir(dirp);
	while (entity != NULL)
	{
		dirname = ft_strjoin(path, entity->d_name);
		if(lstat(dirname, &buf )< 0)
		{
			strerror(lstat(dirname, &buf));
			exit(1);
		}

		if (entity->d_name[0] != '.' || flags->a)
			linearray[i++] = get_info(buf, dirname, ft_strlen(path));
		ft_strdel(&dirname);
		entity = readdir(dirp);
	}
	linearray[i] = NULL;
	closedir(dirp);
	alphabetical(linearray);
	if (flags->t)
	{
		sort_time_a(linearray);
		sort_time(linearray);
	}
	print_arr(linearray, flags);
	return (linearray);
}






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
