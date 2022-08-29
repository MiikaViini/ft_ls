/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:33:38 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/29 21:21:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	initialize_info_struct(t_fileinfo *line)
{
	line->major = 0;
	line->minor = 0;
	ft_memset(line->filename, '\0', MAXNAMLEN);
	ft_memset(line->link, '\0', 256);
	ft_memset(line->m_time, '\0', 17);
	line->size = 0;
}

void	initialize_flags(t_info *info)
{
	info->l = 0;
	info->a = 0;
	info->cap_r = 0;
	info->cap_a = 0;
	info->r = 0;
	info->t = 0;
	info->f = 0;
	info->d = 0;
	info->n = 0;
	info->one_file = 0;
	info->blocks = 0;
	info->f_count = 0;
	info->one = 0;
	info->ret = 0;
}

void	initialize_padds(t_padds *padds)
{
	padds->longest_fname = 0;
	padds->longest_oname = 1;
	padds->longest_ogroup = 1;
	padds->most_links = 0;
	padds->int_len = 1;
	padds->filename_len = 0;
	padds->ownername_len = 0;
	padds->groupname_len = 0;
	padds->biggest = 0;
	padds->longest_link = 0;
}

void	initialize_mc_val(t_mc_val *values)
{
	values->max_cols = 0;
	values->max_rows = 0;
	values->width = 8;
	values->x = 0;
	values->y = 0;
	values->c = '\t';
}

void	free_linearray(t_fileinfo **linearray)
{
	int		i;

	i = -1;
	if (!linearray)
		return ;
	while (linearray[++i])
	{
		ft_strdel(&linearray[i]->owner);
		ft_strdel(&linearray[i]->owner_gr);
		ft_strdel(&linearray[i]->perms);
		free(linearray[i]);
	}
	free(linearray);
}
