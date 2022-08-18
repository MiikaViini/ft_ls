/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:04:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/18 14:14:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_args_time(char **argv, int i)
{
	int			int_temp;
	char		*temp;
	struct stat	buf;
	struct stat	buf2;

	temp = NULL;
	i = move_index(argv, i);
	int_temp = i;
	while (argv[i] && argv[i + 1])
	{
		lstat(argv[i], &buf);
		lstat(argv[i + 1], &buf2);
		if (buf2.st_mtimespec.tv_sec > buf.st_mtimespec.tv_sec)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = int_temp - 1;
		}
		i++;
	}
}

int	move_index(char **arr, int start)
{
	struct stat	buf;
	int			stat;

	stat = 0;
	while (arr[start])
	{
		stat = lstat(arr[start], &buf);
		if (stat == -1 || !S_ISDIR(buf.st_mode))
			start++;
		else
			break ;
	}
	return (start);
}

void	ft_strarrrev(char **arr, int start)
{
	int			len;
	char		*temp;
	int			k;

	temp = NULL;
	k = 0;
	k = start;
	len = start;
	start = move_index(arr, start);
	while (arr[start++])
		len++;
	len += k;
	while (k < len / 2)
	{
		temp = arr[k];
		arr[k] = arr[len - k - 1];
		arr[len - k - 1] = temp;
		k++;
	}
}