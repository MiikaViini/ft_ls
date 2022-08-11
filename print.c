/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:17 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/11 21:53:39 by mviinika         ###   ########.fr       */
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
	most_links = 0;
	if (!linearray[0])
		return ;
	while(linearray[k] != NULL && linearray[k+1] != NULL)
	{
		if (longest_fname < (int)ft_strlen(linearray[k]->filename))
			longest_fname = (int)ft_strlen(linearray[k]->filename);
		if (linearray[0]->biggest <= linearray[k]->size)
			linearray[0]->biggest = linearray[k]->size;
		if (ft_strcmp(linearray[k]->owner, linearray[k + 1]->owner) < 0)
			longest_oname = ft_strlen(linearray[k]->owner);
		if (ft_strcmp(linearray[k]->owner_gr, linearray[k + 1]->owner_gr) < 0)
			longest_ogroup = ft_strlen(linearray[k]->owner);
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
			int_len += ft_intlen(linearray[0]->biggest);
			most_links = ft_intlen(linearray[0]->longest_link);
			ft_printf("total %d\n", flags->blocks);
		}
		while (linearray[++i] != NULL)
		{
			ft_printf("%s  ", linearray[i]->perms);
			ft_printf("%*d ",most_links,linearray[i]->links);
			ft_printf("%-*s  ",longest_oname ,linearray[i]->owner);
			ft_printf("%-*s", longest_ogroup,linearray[i]->owner_gr);
			if (!linearray[i]->major && !linearray[i]->minor)
				ft_printf("  %*lld ",int_len ,linearray[i]->size);
			else
			{
				ft_printf("%12u," ,linearray[i]->major);
				ft_printf("%5u ", linearray[i]->minor);
			}
			ft_printf("%s ", linearray[i]->m_time);
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
