/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/14 14:03:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	find_letter(char c, char *letters)
{
	int	index;

	index = 0;
	while (letters[index])
	{
		if (letters[index] == c)
			return (index);
		index++;
	}
	return (index);
}

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

t_fileinfo	**line_array(char *argv, t_fileinfo **linearray)
{
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;

	int				i;
	char			*temp;
	char			*path;
	temp = ft_strjoin(argv, "/");
	dp = opendir(temp);
	dirp = readdir(dp);
	i = 0;
	while (dirp != NULL)
	{
		path = ft_strjoin(temp, dirp->d_name);
		stat(path, &buf);
		linearray[i] = get_info(buf, path, ft_strlen(temp));
		linearray[0]->total += buf.st_blocks;
		i++;
		// if (dirp->d_type == DT_DIR && ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
		// {
		// 	//ft_printf("stuff from %s\n", argv);
		// 	path = ft_strnew(100);
		// 	path = ft_strjoin(temp, dirp->d_name);
		// 	line_array(path, index, linearray);
		// }
		dirp = readdir(dp);
	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dp);
	return (linearray);
}

int	main(int argc, char **argv)
{
	t_fileinfo	**linearray;
	t_flags		*flags;
	int			count;

	flags = (t_flags*)malloc(sizeof(t_flag));
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 50000);
	count = argc + 1;
	if (argc > 2)
	{
		// taking flags to struct then print
		if (argv[1][0] == '-')
		{
			argv[1]++;
			while (*argv[1] != '\0')
			{
				g_flags[find_letter(*argv[1], FLAGS)](flags, argv[1]);
			}
			return 0;

			// if (argv[1][1] == 'R')
			// {
			// 	recursively(argv[2], linearray);
			// 	print_arr(linearray);
			// 	return (0);
			// }
		}
		while (argc >= 3)
		{
			linearray = line_array(argv[argc - 1], linearray);
			print_arr(linearray);
			argc--;
		}
	}
	else if (argc == 2)
	{
		linearray = line_array(argv[1], linearray);
		print_arr(linearray);
	}
	// else
	// {

	// }
	return (0);
}
