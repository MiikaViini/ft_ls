/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multicolumn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:19:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/29 21:21:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static int	get_tty(void)
{
	struct ttysize	ts;

	ioctl(0, TIOCGWINSZ, &ts);
	return (ts.ts_cols);
}

static void	reset_x(t_mc_val *values)
{
	if (values->y < values->max_rows)
		values->y += 1;
	values->x = 0;
}

void	add_y(t_mc_val *values, int *i)
{
	values->x = 0;
	values->y += 1;
	*i = values->y;
	write(1, "\n", 1);
}

static int	set_values(t_info *info, int name_len, t_mc_val *values)
{
	if (!values)
		return (-1);
	initialize_mc_val(values);
	while (values->width <= name_len)
		values->width += 8;
	if (name_len > get_tty())
	{
		free(values);
		return (-1);
	}
	values->max_cols = get_tty() / values->width;
	values->max_rows = info->f_count / values-> max_cols;
	if ((values->max_cols) * values->width >= get_tty())
		values->c = '\0';
	if (info->f_count % values->max_cols)
		values->max_rows += 1;
	return (0);
}

int	print_multicolumn(t_info *info, t_fileinfo **linearray, t_padds *padds)
{
	int			i;
	int			count;
	t_mc_val	*values;

	count = info->f_count;
	i = 0;
	values = (t_mc_val *)malloc(sizeof(t_mc_val));
	if (set_values(info, padds->longest_fname, values) == -1)
		return (-1);
	while (count-- > 0)
	{
		if (values->x > values->max_cols - 1)
			reset_x(values);
		i = (values->x * values->max_rows) + values->y;
		if (i >= info->f_count)
			add_y(values, &i);
		values->x += 1;
		if (count == 0 || values->x > values->max_cols - 1)
			ft_printf("%s\n", linearray[i]->filename);
		else
			ft_printf("%-*s%c", padds->longest_fname,
				linearray[i]->filename, values->c);
	}
	free(values);
	return (0);
}
