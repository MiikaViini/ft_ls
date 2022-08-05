/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/05 13:27:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	**alphabetical(t_fileinfo **info)
{
	int			i;
	t_fileinfo	*temp;

	i = -1;
	if (!info)
		return (NULL);
	while (info[++i] && info[i + 1])
	{
		if (ft_strcmp(info[i]->filename, info[i + 1]->filename) > 0)
		{
			temp = info[i];
			info[i] = info[i + 1];
			info[i + 1] = temp;
			i = -1;
		}
	}
	return (info);
}

void	sort_time(t_fileinfo **linearray)
{
	int			i;
	t_fileinfo	*temp;

	i = -1;
	temp = NULL;
	while (linearray[++i] && linearray[i + 1])
	{
		if(linearray[i]->time_m < linearray[i + 1]->time_m)
		{
			temp = linearray[i];
			linearray[i] = linearray[i + 1];
			linearray[i + 1] = temp;
			i = -1;
		}
	}
}

void	sort_time_a(t_fileinfo **linearray)
{
	int			i;
	t_fileinfo	*temp;

	i = -1;
	temp = NULL;
	while (linearray[++i] && linearray[i + 1])
	{
		if(linearray[i]->time_a < linearray[i + 1]->time_a)
		{

			temp = linearray[i];
			linearray[i] = linearray[i + 1];
			linearray[i + 1] = temp;
			i = -1;
		}
	}
}

