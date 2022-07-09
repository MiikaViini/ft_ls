/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/09 20:32:47 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// char	*ft_itoa(int n);
// char	*ft_itoabase(unsigned long long int num, int base, int flag);
// char	*ft_strnew(size_t size);
// char	*ft_strcpy(char *dest, const char *src);
// char	*ft_strndup(const char *s, size_t size);
// char	*ft_strdup(const char *s);
// char	*ft_strcat(char *s1, const char *s2);
// char	*ft_strjoin(char const *s1, char const *s2);
// void	ft_bzero(void *s, size_t n);
// size_t	ft_strlen(const char *str);

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

t_fileinfo	**line_array(int argc, char **argv)
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
	temp = ft_strjoin(argv[1], "/");
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
	closedir(dp);
	return (info);
}

int	main(int argc, char **argv)
{
	t_fileinfo	**linearray;
	int			i;

	i = 0;
	if (argc < 2)
	{
		ft_printf("Usage: ./program directory_name\n");
		exit(EXIT_FAILURE);
	}
	linearray = line_array(argc, argv);
	while (linearray[i] != NULL)
	{
		ft_printf("%d", linearray[i]->stat_us);
		ft_printf("%3s ", linearray[i]->perms);
		ft_printf("%3d ", linearray[i]->links);
		ft_printf("%3s ", linearray[i]->owner);
		ft_printf("%3s ", linearray[i]->owner_gr);
		ft_printf("%5lld ", linearray[i]->size);
		ft_printf("%.12s ", linearray[i]->m_time + 4);
		ft_printf("%s\n", linearray[i]->filename);
		i++;
	}
	return (0);
}
