/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:35:10 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/31 13:09:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	path_maker(char *dest, char *dirname)
{
	int			i;

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

int	needs_newline(struct stat buf, char **argv, int i, t_info *flags)
{
	if (flags->one_file != 0)
		if ((argv[i] && lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
			|| (argv[i] && stat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode)))
			write(1, "\n", 1);
	return (argv[i + 1] != NULL && stat(argv[i], &buf) != -1
		&& S_ISDIR(buf.st_mode));
}

void	swap_line(t_fileinfo **linearray, int i, int j, t_fileinfo *temp)
{
	temp = linearray[i];
	linearray[i] = linearray[j];
	linearray[j] = temp;
}

int	treated_like_file(char *str, t_info *flags)
{
	struct stat	buf;
	struct stat	buf2;
	int			res;
	int			res2;

	if (!str)
		return (-1);
	res = lstat(str, &buf);
	res2 = stat(str, &buf2);
	if (res != -1)
	{
		if (!S_ISDIR(buf2.st_mode) || (S_ISLNK(buf.st_mode) && res2 == -1))
			return (2);
		else if (S_ISDIR(buf2.st_mode) && flags->d)
			return (2);
		else if (!S_ISDIR(buf.st_mode) && S_ISDIR(buf2.st_mode) && flags->l)
			return (2);
		else
			return (1);
	}
	return (0);
}
