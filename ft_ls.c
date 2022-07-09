/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/10 01:19:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	*get_info(struct stat buf, char *path, int pathlen)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*time;
	t_fileinfo		*line;

	line = malloc(sizeof(t_fileinfo));
	time = ft_strnew(35);
	line->stat_us = stat(path, &buf);
	ft_strcpy(time, ctime(&buf.st_mtime));
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	line->owner = ft_strdup(pwd->pw_name);
	line->owner_gr = ft_strdup(grp->gr_name);
	line->links = buf.st_nlink;
	line->size = buf.st_size;
	line->filename = ft_strdup(path + pathlen);
	line->perms = permissions(buf.st_mode);
	line->m_time = time;
	return (line);
}

t_fileinfo	**line_array(char *argv, int index, t_fileinfo **linearray)
{
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;

	static int		i;
	char			*temp;
	char			*path;
	//char			*newpath;


	temp = ft_strjoin(argv, "/");
	dp = opendir(temp);
	dirp = readdir(dp);
	//i = 0;
	while (dirp != NULL)
	{
		//i += index;
		path = ft_strjoin(temp, dirp->d_name);
		//ft_printf("%s\n", path);
		stat(path, &buf);
		linearray[i] = get_info(buf, path, ft_strlen(temp));
		i++;
		if (dirp->d_type == DT_DIR && ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
		{
			path = ft_strnew(100);
			path = ft_strjoin(temp, dirp->d_name);
			line_array(path, index, linearray);
		}
		dirp = readdir(dp);
		index++;

	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dp);
	return (linearray);
}

int	main(int argc, char **argv)
{
	t_fileinfo	**linearray;
	int			i;
	int			count;

	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 50000);
	i = 0;
	//linearray = line_array(linearray);
	count = argc + 1;
	if (argc > 2)
	{
		// taking flags to struct then print
		if (ft_strcmp(argv[1], "-R") == 0)
		{
			recursively(argv[2]);
			return (0);
		}
		while (argc >= 3)
		{
			linearray = line_array(argv[argc - 1], i, linearray);
			print_arr(linearray);
			argc--;
		}
	}
	else if (argc == 2)
	{
		linearray = line_array(argv[1], i, linearray);
		print_arr(linearray);
	}
	else
	{
		linearray = line_array(".", i, linearray);
		print_arr(linearray);
	}
	return (0);
}
