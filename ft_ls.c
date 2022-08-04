/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/04 17:35:50 by mviinika         ###   ########.fr       */
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
	t_fileinfo		*line;
	char			link[256];

	line = malloc(sizeof(t_fileinfo));
	ft_memset(line->filename, '\0', MAXNAMLEN);
	ft_memset(link, '\0', 256);
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	line->owner = ft_strdup(pwd->pw_name);
	line->owner_gr = ft_strdup(grp->gr_name);
	line->links = buf.st_nlink;
	line->size = buf.st_size;
	ft_strcat(line->filename, path + pathlen);
	line->blocks = buf.st_blocks;
	line->time_m = buf.st_mtimespec.tv_sec;
	line->time_a = buf.st_mtimespec.tv_nsec;
	if (S_ISLNK(buf.st_mode))
	{
		readlink(path, link, 256);
		ft_strcat(line->filename, " -> ");
		ft_strcat(line->filename, link);
	}
	line->perms = permissions(buf.st_mode, buf);
	line->m_time = ft_strdup(ctime(&buf.st_mtime));
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
		//linearray[0]->total += buf.st_blocks;
		dirp = readdir(dp);
	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dp);
	return (linearray);
}

static void initialize_struct(t_flags *flags)
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
	int			arg_count;
	struct stat		buf;
	//struct	winsize w;

	// ioctl(0, TIOCGWINSZ, &w);
	// printf("lines %d\n", w.ws_row);
	// printf("columsn %d\n", w.ws_col);
	// exit(1);

	i = 0;
	arg_count = 2;
	flags = (t_flags *)malloc(sizeof(t_flags));
	initialize_struct(flags);
	linearray = NULL;
	if (argc > 2 && argv[1][i] == '-')
	{
		while (argv[1][++i] != '\0')
			g_flags[find_letter(argv[1][i], FLAGS)](flags, argv[1]);
		if (argc >= 3)
		{
			while (arg_count < argc)
			{
				if (flags->cap_r)
					recursively(argv[arg_count], linearray, flags);
				else
				{
					ft_opendir(argv[arg_count], linearray, flags, 0);
					//print_arr(linearray, flags);
				}
				arg_count++;
			}

		}
	}
	else if (argc >= 1 && flags->no_flags)
	{
		stat(argv[1], &buf);
		if (S_ISDIR(buf.st_mode))
		{
			ft_opendir(argv[1], linearray, flags, 0);
		}
		else
		{
			linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 1);
			linearray[0] = get_info(buf, argv[1], 0);
			print_arr(linearray, flags);
			free(linearray);
		}

	}
	free(flags);
	return (0);
}
