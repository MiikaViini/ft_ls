/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:35:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/15 14:10:54 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static  void link_maker(t_fileinfo *line, char *path)
{
	char link[256];

	ft_memset(link, '\0', 256);
	readlink(path, link, 256);
	ft_strcat(line->link, " -> ");
	ft_strcat(line->link, link);
}

static void insert_timeinfo(t_fileinfo *line, struct stat buf)
{
	time_t today;
	long l_time;

	line->time_m = buf.st_mtimespec.tv_sec;
	line->time_a = buf.st_mtimespec.tv_nsec;
	l_time = time(&today);
	if (l_time == -1)
	{
		ft_printf("%s\n", strerror(errno));
		free(line);
		exit(1);
	}
	if (l_time - line->time_m < SIX_MONTHS)
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 12);
	else
	{
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 7);
		ft_strcat(line->m_time, " ");
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 20, 4);
	}
}

static void	set_owner_group_info(struct stat buf, t_fileinfo *line)
{
	struct passwd *pwd;
	struct group *grp;

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	if (pwd == NULL)
		line->owner = ft_itoa(buf.st_uid);
	else
		line->owner = ft_strdup(pwd->pw_name);	  // malloc
	if (grp == NULL)
		line->owner = ft_itoa(buf.st_gid);
	else
		line->owner_gr = ft_strdup(grp->gr_name); // malloc
}

static void	set_device_min_maj(struct stat buf, t_fileinfo *line)
{

	if (!S_ISBLK(buf.st_mode) && !S_ISCHR(buf.st_mode))
		line->size = buf.st_size;
	else
	{
		line->minor = (((int32_t)((buf.st_rdev) & 0xffffff)));
		line->major = (((int32_t)(((u_int32_t)(buf.st_rdev) >> 24) & 0xff)));
	}
}

t_fileinfo *get_info(struct stat buf, char *path, int pathlen)
{
	t_fileinfo *line;

	line = malloc(sizeof(t_fileinfo));
	initialize_info_struct(line);
	insert_timeinfo(line, buf);
	set_owner_group_info(buf, line);
	set_device_min_maj(buf, line);
	line->links = buf.st_nlink;
	ft_strcat(line->filename, path + pathlen);
	line->blocks = buf.st_blocks;
	if (S_ISLNK(buf.st_mode))
		link_maker(line, path);
	line->perms = permissions(buf.st_mode, buf);
	return (line);
}