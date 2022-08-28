/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:23:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/28 19:29:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_error(char *dir)
{
	struct stat		buf;
	char			*temp;

	temp = ft_strndup(dir, ft_strlen(dir) - 1);
	if (lstat(temp, &buf) == 0)
		print_err(dir, NOT_DIR);
	else if (lstat(dir, &buf) == -1)
		print_err(dir, NO_ENT);
	else
		print_err(dir, NO_ACCS);
	ft_strdel(&temp);
	return (-1);
}

void	print_err(char *dirname, int error)
{
	if (ft_strrchr(dirname, '/') && error != 2 && error != 9 && error != 20)
	{
		dirname = ft_strrchr(dirname, '/');
		dirname++;
	}
	ft_printf("ft_ls: %s: %s\n", dirname, strerror(error));
}

void	print_flag_err(t_info *flags, char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	ft_printf("%c\nusage: ./ft_ls [-ARadflnrt1] [file ...]\n", c);
	free(flags);
	exit(EXIT_FAILURE);
}
