/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:35:10 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/20 12:42:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	path_maker(char *dest, char *dirname)
{
	int	i;

	i = -1;
	ft_memset(dest, '\0', ft_strlen(dirname) + 2);
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
