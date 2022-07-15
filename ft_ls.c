/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/15 12:36:24 by mviinika         ###   ########.fr       */
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
	char			link[256];

	line = malloc(sizeof(t_fileinfo));
	time = ft_strnew(35);
	//lstat(path, &buf);
	ft_strcpy(time, ctime(&buf.st_mtime));
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	line->owner = ft_strdup(pwd->pw_name);
	line->owner_gr = ft_strdup(grp->gr_name);
	line->links = buf.st_nlink;
	line->size = buf.st_size;
	line->filename = ft_strdup(path + pathlen);
	if (S_ISLNK(buf.st_mode))
	{
		readlink(path, link, 256);
		line->filename = ft_strjoin(line->filename, " -> ");
		line->filename = ft_strjoin(line->filename, link);
	}
	line->perms = permissions(buf.st_mode, buf);
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
	if (!dp || !temp)
		return (NULL);
	dirp = readdir(dp);
	i = 0;
	while (dirp != NULL)
	{
		path = ft_strjoin(temp, dirp->d_name);
		lstat(path, &buf);
		linearray[i++] = get_info(buf, path, ft_strlen(temp));
		linearray[0]->total += buf.st_blocks;
		dirp = readdir(dp);
	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dp);
	return (linearray);
}

static void	initialize_struct(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->cap_r = 0;
	flags->a = 0;
	flags->t = 0;
}

int	main(int argc, char **argv)
{
	t_fileinfo	**linearray;
	t_flags		*flags;
	int			i;

	i = 0;
	flags = (t_flags *)malloc(sizeof(t_flag));
	initialize_struct(flags);
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 50000);
	if (argc > 2 && argv[1][i] == '-')
	{
		while (argv[1][++i] != '\0')
			g_flags[find_letter(argv[1][i], FLAGS)](flags, argv[1]);
		while (argc >= 3)
		{
			linearray = line_array(argv[argc - 1], linearray);
			print_arr(linearray, flags);
			argc--;
		}
	}
	else if (argc == 2)
	{
		linearray = line_array(argv[1], linearray);
		if (linearray == NULL)
		{
			ft_printf("ft_ls: %s: No such file or directory", argv[1]);
			exit(1);
		}
		print_arr(linearray, flags);
	}
	return (0);
}
