/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:13:26 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/22 10:38:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_d_colours(t_fileinfo *line)
{
	if (line->perms[8] == 'w' && line->perms[9] == 't')
		ft_printf(BLK GRNB "%s" C_RES, line->filename);
	else if (line->perms[8] == 'w')
		ft_printf(BLK YELB "%s" C_RES, line->filename);
	else
		ft_printf(BLU "%s" C_RES, line->filename);
}

void	print_colors(t_fileinfo *line)
{
	if (line->perms[0] == 'l')
		ft_printf(MAG "%s"C_RES, line->filename);
	else if (line->perms[0] == 'd')
		print_d_colours(line);
	else if (line->perms[0] == 's')
		ft_printf(GRN "%s" C_RES, line->filename);
	else if (line->perms[0] == 'p')
		ft_printf(YEL "%s" C_RES, line->filename);
	else if (line->perms[0] == 'b')
		ft_printf(BLU CYNB "%ss" C_RES, line->filename);
	else if (line->perms[0] == 'c')
		ft_printf(BLU YELB "%ss" C_RES, line->filename);
	else if (line->perms[3] == 's')
		ft_printf(BLK REDB "%s" C_RES, line->filename);
	else if (line->perms[6] == 's')
		ft_printf(BLK CYNB "%s" C_RES, line->filename);
	else
	{
		if (line->perms[3] == 'x' || line->perms[6] == 'x'
			|| line->perms[9] == 'x')
			ft_printf(RED "%s" C_RES, line->filename);
		else
			ft_printf("%s", line->filename);
	}
}
