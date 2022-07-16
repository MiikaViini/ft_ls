/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:54:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/15 20:41:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	**alphabetical(t_fileinfo **info)
{
	int			i;
	t_fileinfo	*temp;

	i = 0;
	if (!info)
		return (NULL);
	while (info[i] != NULL && info[i + 1] != NULL)
	{
		if (ft_strcmp(info[i]->filename, info[i + 1]->filename) > 0)
		{
			temp = info[i];
			info[i] = info[i + 1];
			info[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	return (info);
}
