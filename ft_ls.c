/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/17 00:08:07 by mviinika         ###   ########.fr       */
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
	//t_fileinfo	***dirs;
	t_fileinfo	**linearray;
	t_dirs		**dirs;
	t_flags		*flags;
	int			i;
	int			k;

	i = 0;
	k = -1;
	flags = (t_flags *)malloc(sizeof(t_flag));
	dirs = (t_dirs **)malloc(sizeof(t_dirs *) * 1000);
	//dirs->dirs = (char **)malloc(sizeof(char *) * 1000);
	initialize_struct(flags);
	//dirs = (t_fileinfo ***)malloc(sizeof(t_fileinfo) * 1000);
	//dirs = (char **)malloc(sizeof(char *) * 1000);
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo *) * 50000);
	if (argc > 2 && argv[1][i] == '-')
	{
		while (argv[1][++i] != '\0')
			g_flags[find_letter(argv[1][i], FLAGS)](flags, argv[1]);
		while (argc >= 3)
		{
			if (flags->cap_r)
				recursively(argv[argc - 1], linearray, dirs);
			else
				linearray = line_array(argv[argc - 1], linearray);
				sort_time_r(dirs);
				// while(dirs[++k])
					
			// ft_printf("%lld %s", dirs[1]->time, ctime(&dirs[1]->time));
			// ft_printf(" %s\n", dirs[1]->dirs);
			// ft_printf("%lld %s", dirs[2]->time, ctime(&dirs[2]->time));
			// ft_printf(" %s", dirs[2]->dirs);
			// alphabetical_s(dirs);
			while(dirs[++k])
			{
				if (k != 0)
				{
					ft_printf("%s:\n", dirs[k]->dirs);
				}
				// ft_printf("%lld %s\n", dirs[k]->time, ctime(&dirs[k]->time));
				// linearray = line_array(dirs[k]->dirs, linearray);
				// print_arr(linearray, flags, dirs);
				// ft_putchar('\n');
			}
			argc--;
		}
	}
	else if (argc == 2)
	{
		linearray = line_array(argv[1], linearray);
		// if (linearray == NULL)
		// {
		// 	ft_printf("ft_ls: %s: No such file or directory", argv[1]);
		// 	exit(1);
		// }
		//print_arr(linearray, flags, dirs);
	}
	return (0);
}
