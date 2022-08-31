/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/31 13:06:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	set_padding_values(t_fileinfo **linearray, t_padds *padds)
{
	int		k;

	k = 0;
	initialize_padds(padds);
	while (linearray[k] != NULL)
	{
		padds->ownername_len = (int)ft_strlen(linearray[k]->owner);
		padds->filename_len = (int)ft_strlen(linearray[k]->filename);
		padds->groupname_len = (int)ft_strlen(linearray[k]->owner_gr);
		if (padds->longest_fname < padds->filename_len)
			padds->longest_fname = padds->filename_len;
		if (padds->biggest < linearray[k]->size)
			padds->biggest = linearray[k]->size;
		if (padds->longest_oname < padds->ownername_len)
			padds->longest_oname = padds->ownername_len;
		if (padds->longest_ogroup < padds->groupname_len)
			padds->longest_ogroup = padds->groupname_len;
		if (padds->longest_link < linearray[k]->links)
			padds->longest_link = linearray[k]->links;
		k++;
	}
}

static void	print_min_maj_nums(t_fileinfo **linearray, int i)
{
	ft_printf("%5u, ", linearray[i]->major);
	if (linearray[i]->minor < 500)
		ft_printf("%3u ", linearray[i]->minor);
	else
		ft_printf("%#010x ", linearray[i]->minor);
}

static void	print_fname(t_fileinfo **linearray,
				t_info *flags, int i, t_padds *padds)
{
	int	padd;
	int	ret;

	padd = 0;
	ret = 0;
	if (!flags->one)
	{
		padd = padds->longest_fname;
		ret = print_multicolumn(flags, linearray, padds);
		flags->f_count = 0;
	}
	if (flags->one || ret == -1)
	{
		while (linearray[++i])
		{
			ft_printf("%s\n", linearray[i]->filename);
		}
	}
}

static void	print_long_format(t_fileinfo **linearray, t_info *info,
	t_padds *padds, int i)
{
	if (info->one_file == 0)
		ft_printf("total %d\n", info->blocks);
	padds->int_len += ft_intlen(padds->biggest);
	padds->most_links = ft_intlen(padds->longest_link);
	while (linearray[++i] != NULL)
	{
		ft_printf("%s", linearray[i]->perms);
		ft_printf("%*d ", padds->most_links, linearray[i]->links);
		ft_printf("%-*s  ", padds->longest_oname, linearray[i]->owner);
		ft_printf("%-*s", padds->longest_ogroup, linearray[i]->owner_gr);
		if (!linearray[i]->major)
			ft_printf("%*lld", padds->int_len, linearray[i]->size);
		else
			print_min_maj_nums(linearray, i);
		ft_printf(" %s ", linearray[i]->m_time);
		ft_printf("%s", linearray[i]->filename);
		ft_printf("%s\n", linearray[i]->link);
	}
}

void	print_arr(t_fileinfo **linearray, t_info *flags)
{
	int			i;
	t_padds		*padds;

	i = -1;
	if (!linearray || !linearray[0])
		return ;
	padds = (t_padds *)malloc(sizeof(t_padds));
	if (!padds)
	{
		flags->ret = 1;
		free_linearray(linearray);
		return ;
	}
	set_padding_values(linearray, padds);
	if (flags->l)
		print_long_format(linearray, flags, padds, i);
	else
		print_fname(linearray, flags, i, padds);
	free(padds);
}
