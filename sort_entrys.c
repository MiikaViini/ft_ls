/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entrys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/19 15:02:13 by mviinika         ###   ########.fr       */
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

void	swap_line(t_fileinfo **linearray, int i, int j, t_fileinfo *temp)
{
	temp = linearray[i];
	linearray[i] = linearray[j];
	linearray[j] = temp;
}

void	ft_quicksort(t_fileinfo **linearray, int first, int last)
{
	int			i;
	int			j;
	int			pivot;
	t_fileinfo	*temp;

	temp = NULL;
	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (ft_strcmp(linearray[i]->filename, linearray[pivot]->filename) < 0 && i < last)
				i++;
			while (ft_strcmp(linearray[j]->filename, linearray[pivot]->filename) > 0)
				j--;
			if (i < j)
				swap_line(linearray, i, j, temp);

		}
		swap_line(linearray, pivot, j, temp);
		ft_quicksort(linearray, first, j - 1);
		ft_quicksort(linearray, j + 1, last);
	}
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
	int i;
	int f_count;

	i = 0;
	f_count = 0;
	while (linearray[++i])
		f_count++;
	if (!flags->f)
	{
		//sort_lexico(linearray);
		ft_quicksort(linearray, 0, f_count - 1);
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
