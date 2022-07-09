/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/09 22:31:17 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_arr(t_fileinfo **linearray)
{
	int	i;

	i = 0;
	while (linearray[i] != NULL)
	{
		ft_printf("%d", linearray[i]->stat_us);
		ft_printf("%3s ", linearray[i]->perms);
		ft_printf("%3d ", linearray[i]->links);
		ft_printf("%3s ", linearray[i]->owner);
		ft_printf("%3s ", linearray[i]->owner_gr);
		ft_printf("%5lld ", linearray[i]->size);
		ft_printf("%.12s ", linearray[i]->m_time + 4);
		ft_printf("%s\n", linearray[i]->filename);
		i++;
	}
}
