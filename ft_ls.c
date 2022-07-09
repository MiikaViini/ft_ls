/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/09 22:36:17 by mviinika         ###   ########.fr       */
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

t_fileinfo	**line_array(int argc, char *argv)
{
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;
	t_fileinfo		**info;
	int				i;
	char			*temp;
	char			*path;

	path = ft_strnew(100);
	info = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 500);
	temp = ft_strnew(100);
	temp = ft_strjoin(argv, "/");
	dp = opendir(temp);
	dirp = readdir(dp);
	i = 0;
	(void)argc;
	while (dirp != NULL)
	{
		path = ft_strjoin(temp, dirp->d_name);
		stat(path, &buf);
		info[i] = get_info(buf, path, ft_strlen(temp));
		dirp = readdir(dp);
		i++;
	}
	info[i] = NULL;
	info = alphabetical(info);
	closedir(dp);
	return (info);
}

int	main(int argc, char **argv)
{
	t_fileinfo	**linearray;
	int			i;
	int			count;

	i = 0;
	count = argc + 1;

	if (argc > 2)
	{
		// taking flags to struct then print
		while (argc >= 3)
		{
			linearray = line_array(argc, argv[argc - 1]);
			print_arr(linearray);
			argc--;
		}
	}
	else if (argc == 2)
	{
		linearray = line_array(argc, argv[1]);
		print_arr(linearray);
	}
	else
	{
		linearray = line_array(argc, ".");
		print_arr(linearray);
	}
	return (0);
}
