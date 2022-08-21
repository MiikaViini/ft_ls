/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/21 22:51:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		ft_printf("%5u ", linearray[i]->minor);
	else
		ft_printf("%#010x ", linearray[i]->minor);
}

static void	print_fname(t_fileinfo **linearray, t_info *flags, int i, t_padds *padds)
{
	int	padd;

	padd = 0;
	if (!flags->one)
	{
		padd = padds->longest_fname;
		get_columns(flags, linearray, padd);
	}
	else
	{
		while (linearray[++i])
		{
			if (flags->cap_g)
				print_colors(linearray[i], padd);
			else
				ft_printf("%s", linearray[i]->filename);
			if (flags->cap_f)
			{
				print_type(linearray[i]->perms);
				write(1, "\n", 1);
			}
			else
				write(1, "\n", 1);
		}
	}

}

static void	print_long_format(t_fileinfo **linearray, t_info *info,
	t_padds *padds, int i)
{
	// char c;

	// c = '\0';
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
		if (info->cap_g)
			print_colors(linearray[i], 0);
		else
			ft_printf("%s", linearray[i]->filename);
		// if (info->cap_f)
		// 	c = print_type(linearray[i]->perms);
		ft_printf("%c%s\n", linearray[i]->link);
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
		return ;
	set_padding_values(linearray, padds);
	if (flags->l)
	{
		print_long_format(linearray, flags, padds, i);
	}
	else
		print_fname(linearray, flags, i, padds);
	free(padds);
}
