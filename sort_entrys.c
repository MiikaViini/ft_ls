/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entrys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/20 17:53:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	comp_ascii(t_fileinfo **linearray, int i, int pivot)
{
	if (ft_strcmp(linearray[i]->filename, linearray[pivot]->filename) > 0)
		return (1);
	else if (ft_strcmp(linearray[i]->filename, linearray[pivot]->filename) < 0)
		return (-1);
	else
		return (0);
}

static int	comp_time(t_fileinfo **linearray, int i, int pivot)
{
	if (linearray[i]->time_m < linearray[pivot]->time_m)
		return (1);
	else if (linearray[i]->time_m > linearray[pivot]->time_m)
		return (-1);
	else
	{
		if (linearray[i]->time_a < linearray[pivot]->time_a)
			return (1);
		else if (linearray[i]->time_a > linearray[pivot]->time_a)
			return (-1);
		else
		{
			if (comp_ascii(linearray, i, pivot) > 0)
				return (1);
			else if (comp_ascii(linearray, i, pivot) < 0)
				return (-1);
			else
				return (0);
		}
		return (0);
	}
}

static void	ft_qsort(t_fileinfo **linearray, int first,
		int last, int (*f)(t_fileinfo **, int, int))
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
			while (f(linearray, i, pivot) < 0 && i < last)
				i++;
			while (f(linearray, j, pivot) > 0)
				j--;
			if (i < j)
				swap_line(linearray, i, j, temp);
		}
		swap_line(linearray, pivot, j, temp);
		ft_qsort(linearray, first, j - 1, f);
		ft_qsort(linearray, j + 1, last, f);
	}
}

static void	sort_reverse(t_fileinfo **linearray, int f_count)
{
	int			i;
	t_fileinfo	*temp;

	i = -1;
	while (++i < f_count / 2)
	{
		temp = linearray[i];
		linearray[i] = linearray[f_count - i - 1];
		linearray[f_count - i - 1] = temp;
	}
}

t_fileinfo	**sort_handler(t_fileinfo **linearray, t_info *flags)
{
	int			i;
	int			f_count;

	i = -1;
	f_count = 0;
	if (!linearray)
		return (NULL);
	while (linearray[++i])
		f_count++;
	if (!flags->f)
	{
		ft_qsort(linearray, 0, f_count - 1, comp_ascii);
		if (flags->t)
			ft_qsort(linearray, 0, f_count - 1, comp_time);
		if (flags->r)
			sort_reverse(linearray, f_count);
	}
	return (linearray);
}
