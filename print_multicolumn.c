/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multicolumn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:19:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/22 13:12:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_tty(void)
{
	struct ttysize	ts;

	ioctl(0, TIOCGWINSZ, &ts);
	return (ts.ts_cols);
}

int	get_columns(t_info *info, t_fileinfo **linearray, t_padds *padds)
{
	int	width;
	int	max_cols;
	int	max_rows;
	int x;
	int y;
	int i;
	int count;
	char c;
	int check;
	int padd;
	int tab;

	tab = 5;
	count = info->f_count;
	width = 8;
	c = '\t';
	x = 0;
	y = 0;
	i = 0;
	check = 0;
	padd = 0;
	while (width < padds->longest_fname)
		width += 8;
	if (padds->longest_fname > get_tty())
		return (0);
	max_cols = get_tty() / width;
	max_rows = info->f_count / max_cols;
	if ((max_cols) * padds->longest_fname >= get_tty())
		c = '\0';
	if (max_cols >= max_rows && max_cols != 0 && max_rows != 0)
	{
		ft_swap(&max_cols, &max_rows);
	}
	if (info->f_count % max_cols != 0)
	{
		max_rows += 1;
		//padds->longest_fname += 1;
	//	padds->longest_fname += 1;
		// max_cols++;
		// max_rows = info->f_count / max_cols;
	}
	// if (info->cap_g && ((max_cols + 1) * padds->longest_fname) < get_tty())
	// {
	// 	padds->longest_fname += 1;
	// 	max_cols++;
	// 	max_rows = info->f_count / max_cols;
	// }
	ft_printf("max_cols * padd: %d max_cols %d, max_rows %d, width %d padd %d\n",max_cols * padds->longest_fname ,max_cols, max_rows, get_tty(), width);
	while (count > 0)
	{
		if (x > max_cols - 1)
		{
			if (y < max_rows)
				y += 1;
			x = 0;
		}
		i = (x * max_rows) + y;
		if (i >= info->f_count)
		{
			x = 0;
			y += 1;
			i = y;
			write(1, "\n", 1);
		}
		count--;
		x += 1;
		if (info->cap_g)
		{
			print_colors(linearray[i]);
			// if (ft_strlen(linearray[i]->filename))
			// 	ft_printf("%d", ft_strlen(linearray[i]->filename) - padds->longest_fname);
			ft_printf("%*c", ((ft_strlen(linearray[i]->filename) - padds->longest_fname)), ' ');
			if (count == 0 || x > max_cols - 1)
				write(1, "\n", 1);
		}
		else if (count == 0 || x > max_cols - 1)
			ft_printf("%s\n", linearray[i]->filename);
		else
			ft_printf("%-*s%c", padds->longest_fname, linearray[i]->filename, c);
		check = 0;
	}
	return (1);
}

// void	print_multicolumn(t_fileinfo **linearray, t_info *info, t_padds *padds)
// {
	
// }
