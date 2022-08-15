/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:33:38 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/15 14:25:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Initialize fileinfo struct
*/
void initialize_info_struct(t_fileinfo *line)
{
	line->major = 0;
	line->minor = 0;
	ft_memset(line->filename, '\0', MAXNAMLEN);
	ft_memset(line->link, '\0', 256);
	ft_memset(line->m_time, '\0', 17);
	line->biggest = 0;
	line->longest_link = 0;
}
/*
** Initialize flags struct
*/
void initialize_flags(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->cap_r = 0;
	flags->r = 0;
	flags->t = 0;
	flags->one_file = 0;
	flags->blocks = 0;
	flags->no_flags = 1;
	flags->haslink = 0;
}
/*
** Delete allocated memory in fileinfo struct
*/
void free_linearray(t_fileinfo **linearray)
{
	int		i;

	i = -1;
	while (linearray[++i])
	{
		ft_strdel(&linearray[i]->owner);
		ft_strdel(&linearray[i]->owner_gr);
		ft_strdel(&linearray[i]->perms);
		free(linearray[i]);
	}
	free(linearray);
}