/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:35:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/05 20:52:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void	link_maker(t_fileinfo *line, char *path)
{
	char	link[255];

	ft_memset(link, '\0', 255);
	readlink(path, link, 255);
	ft_strcat(line->link, " -> ");
	ft_strcat(line->link, link);
}

static void	insert_timeinfo(t_fileinfo *line, struct stat buf)
{
	time_t	now;

	line->time_m = buf.st_mtimespec.tv_sec;
	line->time_a = buf.st_mtimespec.tv_nsec;
	time(&now);
	if (now - line->time_m < SIX_MONTHS && now - line->time_m > -1)
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 12);
	else
	{
		ft_strncat(line->m_time, ctime(&buf.st_mtime) + 4, 7);
		ft_strcat(line->m_time, ft_strrchr(ctime(&buf.st_mtime) + 18, ' '));
		line->m_time[ft_strlen(line->m_time) - 1] = '\0';
	}
}

static void	set_pwd_grp(struct stat buf, t_fileinfo *line, t_info *info)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	if (pwd == NULL || info->n)
		line->owner = ft_itoa(buf.st_uid);
	else
		line->owner = ft_strdup(pwd->pw_name);
	if (grp == NULL || info->n)
		line->owner_gr = ft_itoa(buf.st_gid);
	else
		line->owner_gr = ft_strdup(grp->gr_name);
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

t_fileinfo	*get_info(struct stat buf, char *path, int pathlen, t_info *info)
{
	t_fileinfo	*line;

	lstat(path, &buf);
	line = malloc(sizeof(t_fileinfo));
	if (!line)
		return (NULL);
	info->blocks += buf.st_blocks;
	initialize_info_struct(line);
	insert_timeinfo(line, buf);
	set_pwd_grp(buf, line, info);
	set_device_min_maj(buf, line);
	line->links = buf.st_nlink;
	line->perms = permissions(buf.st_mode, buf, path);
	ft_strcat(line->filename, path + pathlen);
	if (S_ISLNK(buf.st_mode))
		link_maker(line, path);
	return (line);
}
