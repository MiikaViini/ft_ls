/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 23:41:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/10 00:15:58 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursively(char *dirname)
{
	DIR				*dirp;
	struct dirent	*entity;
	//struct stat		buf;
	char			*path;

	dirp = opendir(dirname);
	entity = readdir(dirp);
	path = NULL;
	ft_printf("Reading files from: %s\n", dirname);
	while (entity != NULL)
	{
		ft_printf("%hhd %s\n", entity->d_type, entity->d_name);
		if (entity->d_type == DT_DIR && ft_strcmp(entity->d_name, ".") != 0 && ft_strcmp(entity->d_name, "..") != 0)
		{
			path = ft_strnew(100);
			ft_strcat(path, dirname);
			ft_strcat(path, "/");
			ft_strcat(path, entity->d_name);
			recursively(path);
		}
		entity = readdir(dirp);
	}
}
