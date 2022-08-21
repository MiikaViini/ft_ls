/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multicolumn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:19:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/21 16:26:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_tty(void)
{
	struct ttysize	ts;
	
	ioctl(0, TIOCGWINSZ, &ts);

	// ft_printf("%d", ts.ts_cols);
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

	count = info->f_count;
	width = 8;
	x = 0;
	y = 0;
	i = 0;
	while (width < padds->longest_fname)
		width += 8;
	if (padds->longest_fname > get_tty())
		return (0);
	max_cols = get_tty() / width;
	max_rows = info->f_count / max_cols;
	if (info->f_count % max_cols != 0)
		max_rows += 1;
	while (count > 0)
	{
		if (x > max_cols - 1)
		{
			if (y < max_rows)
				y += 1;
			write(1, "\n", 1);
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
		ft_printf("%-*s	",padds->longest_fname, linearray[i]->filename);
		count--;
		x += 1;
	}
	return 1;
}
