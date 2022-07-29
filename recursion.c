/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/29 22:55:07 by mviinika         ###   ########.fr       */
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

int filecount(char *name)
{
	DIR *d;
	struct dirent	*entity;

	int			count;

	count = 0;
	d = opendir(name);
	if (d == NULL)
		return 0;
	entity = readdir(d);
	while (entity != NULL)
	{
		count++;
		entity = readdir(d);
	}
	closedir(d);
	return (count);
}


void recursively(char *dirname, t_fileinfo **linearray, t_flags *flags, int i)
{
	t_fileinfo		**arr;
	char			path[PATH_MAX];
	int				f_count;

	f_count = filecount(dirname);
	arr = ft_opendir(dirname, linearray, flags, 0, f_count);
	while (i < f_count)
	{
		if (arr[i]->perms[0] == 'd' && ft_strcmp(arr[i]->filename, ".") != 0 && ft_strcmp(arr[i]->filename, "..") != 0)
		{
			ft_memset(path, '\0', PATH_MAX);
			ft_strcat(path, dirname);
			if (ft_strcmp(dirname, "/") != 0)
				ft_strcat(path, "/");
			ft_strcat(path,arr[i]->filename);
			write(1, "\n", 1);
			write(1, path, ft_strlen(path));
			write(1, ":\n", 2);
			recursively(path, arr, flags, 0);

		}
		//flags->filecount--;
		i++;
	}
	//free(arr);

}



t_fileinfo	**ft_opendir(char *dirname, t_fileinfo **linearray, t_flags *flags, int i, int f_count)
{
	DIR				*dirp;
	struct dirent	*entity;
	struct stat		buf;
	//char			*temp;
	char			path[PATH_MAX];

	ft_memset(path, '\0', PATH_MAX);
	ft_strcat(path, dirname);
	ft_strcat(path, "/");
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * f_count);
	(void)f_count;
	dirp = opendir(dirname);
	if (dirp == NULL)
		return NULL;
	entity = readdir(dirp);
	i = 0;
	while (entity != NULL)
	{
		dirname = ft_strjoin(path, entity->d_name);
		lstat(dirname, &buf);
		linearray[i++] = get_info(buf, dirname, ft_strlen(path));
		ft_strdel(&dirname);
		entity = readdir(dirp);
	}
	linearray[i] = NULL;
	closedir(dirp);
	sort_time(linearray);
	print_arr(linearray, flags);
	return (linearray);
	//
	// ft_printf("%s\n", temp);

	// if (flags->cap_r)
	// 	recursively(path, linearray, flags);

	//

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
