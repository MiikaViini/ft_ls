/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:13:26 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/20 21:34:09 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_colors(t_fileinfo *line)
{
	if (line->perms[0] == 'l')
		ft_printf(MAG "%s"C_RES, line->filename);
	else if (line->perms[0] == 'd')
		ft_printf(BLU "%s" C_RES, line->filename);
	else if (line->perms[0] == 's')
		ft_printf(GRN "%s" C_RES, line->filename);
	else if (line->perms[0] == 'p')
		ft_printf(YEL "%s" C_RES, line->filename);
	else if (line->perms[0] == 'b')
		ft_printf(BLU CYNB "%s" C_RES, line->filename);
	else if (line->perms[0] == 'c')
		ft_printf(BLU YELB "%s" C_RES, line->filename);
	else if (line->perms[0] == '-')
	{
		if (line->perms[3] == 'x' || line->perms[6] == 'x' || line->perms[9] == 'x')
			ft_printf(RED "%s" C_RES, line->filename);
		else
			ft_printf("%s", line->filename);
	}
	else if (line->perms[3] == 's')
		ft_printf(BLK RED "%s" C_RES, line->filename);
	else if (line->perms[6] == 's')
		ft_printf(BLK CYN "%s" C_RES, line->filename);
	else if (line->perms[0] == '-' && line->perms[8] == 'w' && line->perms[9] == 't')
		ft_printf(BLK GRN "%s" C_RES, line->filename);
	else if (line->perms[0] == '-' && line->perms[8] == 'w')
		ft_printf(BLK YEL "%s" C_RES, line->filename);
	else
		ft_printf("%s", line->filename);
}
