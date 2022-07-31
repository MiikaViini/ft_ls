/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/31 12:33:23 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_arr(t_fileinfo **linearray, t_flags *flags)
{
	int			i;
	int			k;
	int			blocks;

	i = 0;
	k = 0;
	blocks = 0;
	(void)flags;
	while(linearray[i] != NULL)
		blocks += linearray[i++]->blocks;
	ft_printf("total %d\n", blocks);
	i = 0;
	while (linearray[i] != NULL)
	{
		// if (!flags->a)
		// 	while (linearray[i]->filename[0] == '.')
		// 		i++;
		// if (linearray[i]->perms[0] == 'd')
		// 	ft_printf("%s\n", dirs[k++]);
		ft_printf("%3s ", linearray[i]->perms);
		ft_printf("%4d ", linearray[i]->links);
		ft_printf("%3s ", linearray[i]->owner);
		ft_printf("%3s ", linearray[i]->owner_gr);
		ft_printf("%7lld ", linearray[i]->size);
		ft_printf("%.12s ", linearray[i]->m_time + 4);
		ft_printf("%s\n", linearray[i]->filename);
		i++;
	}
}

// void make_array(t_fileinfo **linearray, char *path,)
// {
// 	DIR				*dirp;
// 	struct dirent	*entity;
// 	//struct dirent	*entity_p;
// 	char			*path;
// 	//struct stat		buf;
// 	char			*temp;


// 	*linearray++ =
// }

// void	print_arr_R(t_fileinfo **linearray)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("total %d\n", linearray[i]->total);
// 	while (linearray[i] != NULL)
// 	{
// 		ft_printf("%d", linearray[i]->stat_us);
// 		ft_printf("%3s ", linearray[i]->perms);
// 		ft_printf("%3d ", linearray[i]->links);
// 		ft_printf("%3s ", linearray[i]->owner);
// 		ft_printf("%3s ", linearray[i]->owner_gr);
// 		ft_printf("%5lld ", linearray[i]->size);
// 		ft_printf("%.12s ", linearray[i]->m_time + 4);
// 		ft_printf("%s\n", linearray[i]->filename);
// 		i++;
// 	}
// }

