/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/09 14:47:07 by mviinika         ###   ########.fr       */
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

void	link_maker(t_fileinfo *line, char *path)
{
	char	link[256];

	ft_memset(link, '\0', 256);
	readlink(path, link, 256);
	ft_strcat(line->filename, " -> ");
	ft_strcat(line->filename, link);
}

static void	initialize_info_struct(t_fileinfo *line)
{
	line->major = 0;
	line->minor = 0;
	ft_memset(line->filename, '\0', MAXNAMLEN);
	ft_memset(line->m_time, '\0', 17);
	line->biggest = 0;
	line->longest_link = 0;
	
}

static void insert_timeinfo(t_fileinfo *line, struct stat buf)
{
	time_t today;

	long	l_time;
	
	line->time_m = buf.st_mtimespec.tv_sec;
	line->time_a = buf.st_mtimespec.tv_nsec;
	l_time = time(&today);
	if (l_time == -1)
	{
		ft_printf("%s\n", strerror(errno));
		free(line);
		exit(1);
	}
	if ( l_time - line->time_m < SIX_MONTHS)
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 12);
	else
	{
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 7);
		ft_strcat(line->m_time, " ");
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 20, 4);
	}
}

t_fileinfo	*get_info(struct stat buf, char *path, int pathlen)
{
	struct passwd	*pwd;
	struct group	*grp;
	t_fileinfo		*line;

	line = malloc(sizeof(t_fileinfo));
	initialize_info_struct(line);
	insert_timeinfo(line, buf);
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	line->owner = ft_strdup(pwd->pw_name);
	line->owner_gr = ft_strdup(grp->gr_name);
	line->links = buf.st_nlink;
	if (!S_ISBLK(buf.st_mode) && !S_ISCHR(buf.st_mode))
		line->size = buf.st_size;
	else
	{
		line->minor = (((int32_t)((buf.st_rdev) & 0xffffff)));
		line->major = (((int32_t)(((u_int32_t)(buf.st_rdev) >> 24) & 0xff)));
	}
	ft_strcat(line->filename, path + pathlen);
	line->blocks = buf.st_blocks;
	if (S_ISLNK(buf.st_mode))
		link_maker(line, path);
	line->perms = permissions(buf.st_mode, buf);
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
		dirp = readdir(dp);
	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dp);
	return (linearray);
}

static void	initialize_flags(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->cap_r = 0;
	flags->r = 0;
	flags->t = 0;
	flags->one_file = 0;
	flags->blocks = 0;
	flags->no_flags = 1;
}

static int get_flags(char **argv, t_flags *flags)
{
	int	i;
	int k;

	initialize_flags(flags);
	k = 1;
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		while (argv[i][k] != '\0')
			g_flags[find_letter(argv[i][k++], FLAGS)](flags, argv[i]);
		k = 1;
		i++;
	}
		
	return (i - 1);
}

int ft_ls(int argc, char **argv)
{
	t_fileinfo 	**linearray;
	t_flags		*flags;
	char		path[PATH_MAX];
	int			i;
	
	i = 1;
	ft_memset(path, '\0', PATH_MAX);
	path[0] = '.';
	flags = (t_flags *)malloc(sizeof(t_flags));
	linearray = NULL;
	if (argc == 1 || (argv[i] && ft_strcmp(argv[i], "--") == 0))
		ft_opendir(path, linearray, flags, 0);
	else
	{
		i = get_flags(argv, flags);
		while (argv[i])
		{
			i++;
			if (argv[i])
				path_maker(path, argv[i]);
			if (flags->cap_r)
				recursively(path, linearray, flags);
			else
				ft_opendir(path, linearray, flags, 0);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	//t_fileinfo	**linearray;
	//t_flags		*flags;
	//struct stat		buf;
	//char		path[PATH_MAX];

	
	ft_ls(argc, argv);
	//exit(1);
	// linearray = NULL;
	// if (argv[1] && argv[1][i] == '-')
	// {
	// 	while (argv[1][++i] != '\0')
	// 		g_flags[find_letter(argv[1][i], FLAGS)](flags, argv[1]);
	// 	if (argc >= 3)
	// 	{
	// 		while (arg_count < argc)
	// 		{
	// 			if (lstat(argv[arg_count], &buf) < 0)
	// 				print_err(argv[arg_count], errno);
	// 			else if (!S_ISDIR(buf.st_mode))
	// 			{
	// 				flags->one_file = 1;
	// 				linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 2);
	// 				linearray[0] = get_info(buf, argv[arg_count], 0);
	// 				linearray[1] = NULL;
	// 				print_arr(linearray, flags);
	// 				free(linearray);
	// 			}
	// 			else if (flags->cap_r)
	// 				recursively(argv[arg_count], linearray, flags);
	// 			else
	// 				ft_opendir(argv[arg_count], linearray, flags, 0);
	// 			arg_count++;
	// 		}
	// 	}
	// }
	// else if (argc >= 1 && flags->no_flags)
	// {
	// 	if (argc == 1)
	// 		ft_strcat(path, ".");
	// 	else
	// 		ft_strcat(path, argv[1]);
	// 	stat(path, &buf);
	// 	if (S_ISDIR(buf.st_mode))
	// 	{
	// 		ft_opendir(path, linearray, flags, 0);
	// 	}
	// 	else
	// 	{
	// 		linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 1);
	// 		linearray[0] = get_info(buf, path, 0);
	// 		print_arr(linearray, flags);
	// 	}
	// }
	//free(linearray);
	//free(flags);
	return (0);
}


