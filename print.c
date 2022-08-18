/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/18 12:51:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
static void	set_padding_values(t_fileinfo **linearray, t_padds *padds)
{
	int		k;
	
	k = 0;
	initialize_padds(padds);
	while(linearray[k] != NULL)
	{
		padds->ownername_len = (int)ft_strlen(linearray[k]->owner);
		padds->filename_len = (int)ft_strlen(linearray[k]->filename);
		padds->groupname_len = (int)ft_strlen(linearray[k]->owner_gr);
		if (padds->longest_fname < padds->filename_len)
			padds->longest_fname = padds->filename_len;
		if (linearray[0]->biggest <= linearray[k]->size)
			linearray[0]->biggest = linearray[k]->size;
		if (padds->longest_oname < padds->ownername_len)
			padds->longest_oname = padds->ownername_len;
		if (padds->longest_ogroup < padds->groupname_len)
			padds->longest_ogroup = padds->groupname_len;
		if (linearray[0]->longest_link < linearray[k]->links)
			linearray[0]->longest_link = linearray[k]->links;
		k++;
	}
}

static void print_min_maj_nums(t_fileinfo **linearray, int i)
{
	ft_printf("%12u, " ,linearray[i]->major);
	if (linearray[i]->minor < 500)
		ft_printf("%5u ", linearray[i]->minor);
	else
		ft_printf("%#010x ", linearray[i]->minor);
}

static void print_long_format(t_fileinfo **linearray, t_flags *flags, t_padds *padds, int i)
{
	if (flags->one_file == 0)
			ft_printf("total %d\n", flags->blocks);
	padds->int_len += ft_intlen(linearray[0]->biggest);
	padds->most_links = ft_intlen(linearray[0]->longest_link);
	while (linearray[++i] != NULL)
	{
		ft_printf("%s", linearray[i]->perms);
		ft_printf("%*d ",padds->most_links,linearray[i]->links);
		ft_printf("%-*s  ",padds->longest_oname ,linearray[i]->owner);
		ft_printf("%-*s", padds->longest_ogroup,linearray[i]->owner_gr);
		if (!linearray[i]->major && !linearray[i]->minor)
			ft_printf("%*lld ",padds->int_len + 1,linearray[i]->size);
		else
		{
			print_min_maj_nums(linearray, i);
			// ft_printf("%12u, " ,linearray[i]->major);
			// if (linearray[i]->minor < 500)
			// 	ft_printf("%5u ", linearray[i]->minor);
			// else
			// 	ft_printf("%#010x ", linearray[i]->minor);
		}
		ft_printf("%s ", linearray[i]->m_time);
		ft_putstr(linearray[i]->filename);
		ft_putendl(linearray[i]->link);
	}
}

void	print_arr(t_fileinfo **linearray, t_flags *flags)
{
	int			i;
	t_padds		*padds;
	//int			k;

	// int			longest_fname;
	// int			longest_oname;
	// int			longest_ogroup;
	// int			most_links;
	// size_t		int_len;
	// int			filenamelen;
	// int			ownernamelen;
	// int			groupnamelen;

	i = -1;
	//k = 0;
	// int_len = 0;
	// longest_oname = 1;
	// longest_ogroup = 1;
	// longest_fname = 0;
	// filenamelen = 0;
	// ownernamelen = 0;
	// groupnamelen = 0;
	// most_links = 0;
	padds = (t_padds *)malloc(sizeof(t_padds));
	if (!linearray || !linearray[0])
		return ;
	set_padding_values(linearray, padds);
	// while(linearray[k] != NULL)
	// {
	// 	padds->ownername_len = (int)ft_strlen(linearray[k]->owner);
	// 	padds->filename_len = (int)ft_strlen(linearray[k]->filename);
	// 	padds->groupname_len = (int)ft_strlen(linearray[k]->owner_gr);
	// 	if (padds->longest_fname < padds->filename_len)
	// 		padds->longest_fname = padds->filename_len;
	// 	if (linearray[0]->biggest <= linearray[k]->size)
	// 		linearray[0]->biggest = linearray[k]->size;
	// 	if (padds->longest_oname < padds->ownername_len)
	// 		padds->longest_oname = padds->ownername_len;
	// 	if (padds->longest_ogroup < padds->groupname_len)
	// 		padds->longest_ogroup = padds->groupname_len;
	// 	if (linearray[0]->longest_link < linearray[k]->links)
	// 		linearray[0]->longest_link = linearray[k]->links;
	// 	k++;
	// }
	if (flags->l)
	{
		print_long_format(linearray, flags, padds, i);
		// if (flags->one_file == 0)
		// 	ft_printf("total %d\n", flags->blocks);
		// int_len += ft_intlen(linearray[0]->biggest);
		// most_links = ft_intlen(linearray[0]->longest_link);
		// while (linearray[++i] != NULL)
		// {
		// 	ft_printf("%s", linearray[i]->perms);
		// 	ft_printf("%*d ",most_links,linearray[i]->links);
		// 	ft_printf("%-*s  ",longest_oname ,linearray[i]->owner);
		// 	ft_printf("%-*s", longest_ogroup,linearray[i]->owner_gr);
		// 	if (!linearray[i]->major && !linearray[i]->minor)
		// 		ft_printf("%*lld ",int_len + 1,linearray[i]->size);
		// 	else
		// 	{
		// 		ft_printf("%12u, " ,linearray[i]->major);
		// 		if (linearray[i]->minor < 500)
		// 			ft_printf("%5u ", linearray[i]->minor);
		// 		else
		// 			ft_printf("%#010x ", linearray[i]->minor);
		// 	}
		// 	ft_printf("%s ", linearray[i]->m_time);
		// 	ft_putstr(linearray[i]->filename);
		// 	ft_putendl(linearray[i]->link);
		//}
	}
	else
	{
		while (linearray[++i])
			ft_printf("%s\n", linearray[i]->filename);
	}
}
