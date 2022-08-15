/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/15 14:12:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_arr(t_fileinfo **linearray, t_flags *flags)
{
	int			i;
	int			k;
	int			longest_fname;
	int			longest_oname;
	int			longest_ogroup;
	int			most_links;
	int 		filecount;
	size_t		int_len;

	i = -1;
	k = 0;
	filecount = 0;
	int_len = 0;
	longest_oname = 1;
	longest_ogroup = 1;
	longest_fname = 0;
	most_links = 0;
	if (!linearray)
		return ;
	while(linearray[k] != NULL)
	{
		if (longest_fname < (int)ft_strlen(linearray[k]->filename))
			longest_fname = (int)ft_strlen(linearray[k]->filename);
		if (linearray[0]->biggest <= linearray[k]->size)
			linearray[0]->biggest = linearray[k]->size;
		if (longest_oname < (int)ft_strlen(linearray[k]->owner))
			longest_oname = ft_strlen(linearray[k]->owner);
		if (longest_ogroup < (int)ft_strlen(linearray[k]->owner_gr))
			longest_ogroup = (int)ft_strlen(linearray[k]->owner_gr);
		if (linearray[0]->longest_link < linearray[k]->links)
			linearray[0]->longest_link = linearray[k]->links;
		k++;
		//blocks += linearray[k++]->blocks;
		filecount++;
	}
	if (flags->l)
	{
		if (flags->one_file == 0)
		{
			ft_printf("total %d\n", flags->blocks);
		}
		int_len += ft_intlen(linearray[0]->biggest);
		most_links = ft_intlen(linearray[0]->longest_link);
		while (linearray[++i] != NULL)
		{
			ft_printf("%s  ", linearray[i]->perms);
			ft_printf("%*d ",most_links,linearray[i]->links);
			ft_printf("%-*s  ",longest_oname ,linearray[i]->owner);
			ft_printf("%-*s", longest_ogroup,linearray[i]->owner_gr);
			if (!linearray[i]->major && !linearray[i]->minor)
				ft_printf("%*lld ",int_len+2,linearray[i]->size);
			else
			{
				ft_printf("%12u, " ,linearray[i]->major);
				if (linearray[i]->minor < 500)
					ft_printf("%5u ", linearray[i]->minor);
				else
					ft_printf("%#010x ", linearray[i]->minor);
			}
			ft_printf("%s ", linearray[i]->m_time);
			
			
			ft_putstr(linearray[i]->filename);
			ft_putendl(linearray[i]->link);
				// ft_printf("%s", linearray[i]->filename);
				// ft_printf("%s\n", linearray[i]->link);
			
			//	ft_printf("%s\n", linearray[i]->filename);
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
