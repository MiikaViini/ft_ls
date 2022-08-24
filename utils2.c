/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:35:10 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/24 15:58:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	path_maker(char *dest, char *dirname, t_info *info)
{
	int			i;
	int			i_stat;
	struct stat	buf;
	char		link[255];

	i = -1;
	i_stat = lstat(dirname, &buf);
	if (S_ISLNK(buf.st_mode) && !info->l)
	{
		ft_printf("%s", dirname);
		ft_memset(link, '\0', 255);
		readlink(dirname, link, 255);
		ft_memset(dirname, '\0', 255);
		ft_strcat(dirname, "/");
		ft_strcat(dirname, link);
	}
	ft_memset(dest, '\0', 255);
	while (dirname[++i])
		dest[i] = dirname[i];
	if (dest[i] != '/')
		dest[i++] = '/';
	dest[i] = '\0';
}

int	newpath(char *path, char **argv, int i)
{
	if (argv[i] && ft_strcmp(argv[i], "--") == 0 && argv[i + 1] != NULL)
	{
		i++;
		ft_strcpy(path, argv[i]);
	}
	return (i);
}

int	needs_newline(struct stat buf, char **argv, int i)
{
	return (argv[i + 1] != NULL && lstat(argv[i], &buf) != -1
		&& S_ISDIR(buf.st_mode));
}

void	swap_line(t_fileinfo **linearray, int i, int j, t_fileinfo *temp)
{
	temp = linearray[i];
	linearray[i] = linearray[j];
	linearray[j] = temp;
}
