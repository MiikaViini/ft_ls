/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/16 23:52:50 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	**alphabetical(t_fileinfo **info)
{
	int			i;
	t_fileinfo	*temp;

	i = 0;
	if (!info)
		return (NULL);
	while (info[i] != NULL && info[i + 1] != NULL)
	{
		if (ft_strcmp(info[i]->filename, info[i + 1]->filename) > 0)
		{
			temp = info[i];
			info[i] = info[i + 1];
			info[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	return (info);
}

void	alphabetical_s(char **dirs)
{
	int			i;
	char		*temp;

	i = 0;
	if (!dirs)
		return ;
	while (dirs[i] != NULL && dirs[i + 1] != NULL)
	{
		if (ft_strcmp(dirs[i], dirs[i + 1]) > 0)
		{
			temp = dirs[i];
			dirs[i] = dirs[i + 1];
			dirs[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	sort_time_r(t_dirs **dirs)
{
	int			i;
	t_dirs		*temp;

	i = 0;
	if (!dirs)
		return ;
	while (dirs[i] != NULL && dirs[i + 1] != NULL)
	{
		if (dirs[i]->time < dirs[i + 1]->time)
		{
			temp = dirs[i];
			dirs[i] = dirs[i + 1];
			dirs[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}
