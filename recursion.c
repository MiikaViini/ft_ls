/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/14 08:51:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursively(char *dirname,int i, t_fileinfo **linearray)
{
	DIR				*dirp;
	struct dirent	*entity;
	char			*path_;
	struct stat		buf;
	char			*temp;
	//int				count;


	temp = ft_strjoin(dirname, "/");
	dirp = opendir(dirname);
	entity = readdir(dirp);
	ft_printf("Reading files from: %s\n",dirname);
	while (entity != NULL)
	{
		path_ = ft_strjoin(temp, entity->d_name);
		stat(path_, &buf);
		ft_printf(" %d %hhd %s\n",i, entity->d_type, entity->d_name);
		linearray[i++] = get_info(buf, path_, 0);
		linearray[0]->total += buf.st_blocks;

		if (entity->d_type == DT_DIR && ft_strcmp(entity->d_name, ".") != 0 && ft_strcmp(entity->d_name, "..") != 0)
		{
			recursively(path_, i, linearray);
		}
		entity = readdir(dirp);
	}
	//linearray = alphabetical(linearray);
	//dir_tree[i] = NULL;
	//closedir(dirp);

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
