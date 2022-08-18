/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:23:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/18 17:10:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_err(char *dirname, int error)
{
	if (*dirname && *dirname == '/')
		dirname++;
	ft_printf("ft_ls: %s: %s \n", dirname, strerror(error));
}

void	print_flag_err(t_flags *flags, char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	ft_printf("%c\nusage: ./ft_ls [-ARaflrt] [file ...]\n", c);
	free(flags);
	exit(EXIT_FAILURE);
}
