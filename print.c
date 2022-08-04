/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/04 23:22:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_arr(t_fileinfo **linearray, t_flags *flags)
{
	int			i;
	int			k;
	int			order;
	int			blocks;
	int			longest_name;
	int 		filecount;
	size_t		int_len;

	i = -1;
	k = 0;
	blocks = 0;
	order = 4;
	filecount = 0;
	int_len = 1;
	(void)flags;
	// linearray[0]->size = linearray[0]->biggest;
	while(linearray[k] != NULL)
	{
		if (k >= 1 && ft_strcmp(linearray[k]->filename, linearray[k - 1]->filename) > 0)
			longest_name = (int)ft_strlen(linearray[k]->filename);
		if (linearray[0]->biggest <= linearray[k]->size)
			linearray[0]->biggest = linearray[k]->size;
		blocks += linearray[k++]->blocks;
		filecount++;
	}

	if (flags->l)
	{
		int_len += ft_intlen(linearray[0]->biggest);
		ft_printf("total %d\n", blocks);
		while (linearray[++i] != NULL)
		{
			ft_printf("%3s ", linearray[i]->perms);
			ft_printf("%4d ", linearray[i]->links);
			ft_printf("%4s  ", linearray[i]->owner);
			ft_printf("%4s ", linearray[i]->owner_gr);
			ft_printf("%*lld ",int_len ,linearray[i]->size);
			ft_printf("%.12s ", linearray[i]->m_time + 4);
			ft_printf("%s\n", linearray[i]->filename);
		}
	}
	else
	{
		while (linearray[++i])
		{
			// if (i > 0 && i % 4 == 0)
			// 	ft_putchar('\n');
			ft_printf("%s\n", linearray[i]->filename);
			// ft_printf("%-*s	",longest_name * 3, linearray[i]->filename);


		}
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

