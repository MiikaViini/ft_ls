/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/14 11:20:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursively(char *dirname, t_fileinfo **linearray)
{
	DIR				*dirp;
	struct dirent	*entity;
	struct stat		buf;
	char			*temp;
	static int		i;

	temp = ft_strjoin(dirname, "/");
	dirp = opendir(dirname);
	entity = readdir(dirp);
	while (entity != NULL)
	{
		dirname = ft_strjoin(temp, entity->d_name);
		stat(dirname, &buf);
		linearray[i++] = get_info(buf, dirname, 0);
		linearray[0]->total += buf.st_blocks;
		if (entity->d_type == DT_DIR && ft_strcmp(entity->d_name, ".") != 0
			&& ft_strcmp(entity->d_name, "..") != 0)
			recursively(dirname, linearray);
		entity = readdir(dirp);
	}
	linearray[i] = NULL;
	linearray = alphabetical(linearray);
	closedir(dirp);
}

// {
// 	DIR				*dp;
// 	struct dirent	*dirp;
// 	struct stat		buf;

// 	int				i;
// 	char			*temp;
// 	char			*path;
// 	temp = ft_strjoin(argv, "/");
// 	dp = opendir(temp);
// 	dirp = readdir(dp);
// 	i = 0;
// 	while (dirp != NULL)
// 	{
// 		path = ft_strjoin(temp, dirp->d_name);
// 		stat(path, &buf);
// 		linearray[i] = get_info(buf, path, ft_strlen(temp));
// 		linearray[0]->total += buf.st_blocks;
// 		i++;
// 		// if (dirp->d_type == DT_DIR && ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
// 		// {
// 		// 	//ft_printf("stuff from %s\n", argv);
// 		// 	path = ft_strnew(100);
// 		// 	path = ft_strjoin(temp, dirp->d_name);
// 		// 	line_array(path, index, linearray);
// 		// }
// 		dirp = readdir(dp);
// 	}
// 	linearray[i] = NULL;
// 	linearray = alphabetical(linearray);
// 	closedir(dp);
// 	return (linearray);
// }
