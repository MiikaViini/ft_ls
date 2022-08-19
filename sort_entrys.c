/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entrys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/19 11:03:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	**sort_lexico(t_fileinfo **info)
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
		if (linearray[i]->time_m < linearray[i + 1]->time_m)
		{
			temp = linearray[i];
			linearray[i] = linearray[i + 1];
			linearray[i + 1] = temp;
			i = -1;
		}
	}
}

// void	sort_time_a(t_fileinfo **linearray)
// {
// 	int			i;
// 	t_fileinfo	*temp;

// 	i = -1;
// 	temp = NULL;
// 	while (linearray[++i] && linearray[i + 1])
// 	{
// 		ft_printf("linearray[i]:%lu	linearray[i + 1]:%lu\n", linearray[i]->time_a, linearray[i + 1]->time_a);
// 		if (linearray[i]->time_a > linearray[i + 1]->time_a)
// 		{
// 			ft_printf("it was\n");
// 			temp = linearray[i];
// 			linearray[i] = linearray[i + 1];
// 			linearray[i + 1] = temp;
// 			i = -1;
// 		}
// 	}
// 	exit(1);
// }

void	sort_reverse(t_fileinfo **linearray)
{
	int			i;
	int			f_count;
	t_fileinfo	*temp;

	i = -1;
	f_count = 0;
	temp = NULL;
	while (linearray[++i])
		f_count++;
	i = -1;
	while (++i < f_count / 2)
	{
		temp = linearray[i];
		linearray[i] = linearray[f_count - i - 1];
		linearray[f_count - i - 1] = temp;
	}
}

t_fileinfo	**sort_handler(t_fileinfo **linearray, t_flags *flags)
{
	if (!flags->f)
	{
		sort_lexico(linearray);
		if (flags->t)
		{
			sort_time(linearray);
			//sort_time_a(linearray);
		}
		if (flags->r)
			sort_reverse(linearray);
	}
	return (linearray);
}
