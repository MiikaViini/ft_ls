/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/25 14:36:48 by mviinika         ###   ########.fr       */
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

void	alphabetical_s(t_dirs **dirs)
{
	int			i;
	t_dirs		*temp;

	i = 0;
	if (!dirs)
		return ;
	while (dirs[i] != NULL && dirs[i + 1] != NULL)
	{
		if (ft_strcmp(dirs[i]->dirs, dirs[i + 1]->dirs) > 0)
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
		if(dirs[i]->time_i < dirs[i + 1]->time_i)
		{
			temp = dirs[i];
			dirs[i] = dirs[i + 1];
			dirs[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	sort_time(t_fileinfo **linearray)
{
	int			i;
	t_fileinfo		*temp;

	i = 0;
	if (!linearray)
		return ;

	while (linearray[i] != NULL && linearray[i + 1] != NULL)
	{
		if(linearray[i]->time_i < linearray[i + 1]->time_i)
		{

			temp = linearray[i];
			linearray[i] = linearray[i + 1];
			linearray[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	sort_depth_r(t_dirs **dirs)
{
	int			i;
	t_dirs		*temp;

	i = 0;
	if (!dirs)
		return ;

	while (dirs[i] != NULL && dirs[i + 1] != NULL)
	{
		if (dirs[i]->depth > dirs[i + 1]->depth)
		{
			temp = dirs[i];
			dirs[i] = dirs[i + 1];
			dirs[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	sort_recu_r(t_dirs **dirs)
{
	int			i;
	int			d;
	t_dirs		*temp;
	char 		*root;

	i = 0;
	d = 1;
	if (!dirs)
		return ;

	root = dirs[d++]->dirs;
	while (dirs[i] != NULL && dirs[i + 1] != NULL)
	{
		if (ft_strncmp(dirs[i]->dirs, root,ft_strlen(root)) == 0)
		{
			temp = dirs[i];
			dirs[i] = dirs[i + 1];
			dirs[i + 1] = temp;
			i = 0;
		}
		i++;
		if (dirs[i]->depth == 1)
			root = dirs[d++]->dirs;
	}
}


