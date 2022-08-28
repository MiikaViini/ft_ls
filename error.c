/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:23:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/28 22:08:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_err(char *dirname)
{
	errno_t	err;

	err = 0;
	if (ft_strrchr(dirname, '/') && err != 2 && err != 9 && err != 20)
	{
		dirname = ft_strrchr(dirname, '/');
		dirname++;
	}
	ft_printf("ft_ls: %s: ", dirname);
	perror(NULL);
}

void	print_flag_err(t_info *flags, char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	ft_printf("%c\nusage: ./ft_ls [-ARadflnrt1] [file ...]\n", c);
	free(flags);
	exit(EXIT_FAILURE);
}
