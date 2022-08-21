/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multicolumn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:19:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/21 23:38:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_tty(void)
{
	struct ttysize	ts;

	ioctl(0, TIOCGWINSZ, &ts);
	return (ts.ts_cols);
}

int	get_columns(t_info *info, t_fileinfo **linearray, int padd)
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

	count = info->f_count;
	width = 8;
	c = '\0';
	x = 0;
	y = 0;
	i = 0;
	check = 0;
	while (width < padd)
		width += 8;
	if (padd > get_tty())
		return (0);
	max_cols = get_tty() / width;
	max_rows = info->f_count / max_cols;
	if (info->f_count % max_cols != 0)
		max_rows += 1;
	if (info->cap_g)
	{
		max_cols++;
		max_rows = info->f_count / max_cols;
		padd += 1;
	}
	while (count > 0)
	{
		if (x > max_cols - 1)
		{
			if (y < max_rows)
				y += 1;
			// if(info->cap_g)
			// 	write(1, "\n", 1);
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
			// if (count == 0 || x > max_cols - 1)
			// 	padd = 1;
			print_colors(linearray[i], padd);
			if (count == 0)
				write(1, "\n", 1);
		}
		else if (count == 0 || x > max_cols - 1)
			ft_printf("%s\n", linearray[i]->filename);
		else
			ft_printf("%-*s", padd + 5, linearray[i]->filename);
		check = 0;

	}
	return (1);
}

// void	print_multicolumn(t_fileinfo **linearray, t_info *info, t_padds *padds)
// {
	
// }
