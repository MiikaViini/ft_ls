/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:23:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/22 22:28:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_err(char *dirname, int error)
{
	if (ft_strrchr(dirname, '/') && error != 2 && error != 9)
	{
		dirname = ft_strrchr(dirname, '/');
		dirname++;
	}
	ft_printf("ft_ls: %s: %s\n", dirname, strerror(error));
}

void	print_flag_err(t_info *flags, char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	ft_printf("%c\nusage: ./ft_ls [-1ARadflnrt] [file ...]\n", c);
	free(flags);
	exit(EXIT_FAILURE);
}
