/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:36:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/20 19:33:06 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_single_arg(int argc, char *path, int i)
{
	return (argc == 1 || (argc == 2
			&& ft_strcmp(path, ".") == 0) || argc - i <= 1);
}

int	is_single_file(struct stat buf, char **argv, int i, t_info *flags)
{
	return ((lstat(argv[i], &buf) != -1 && !S_ISDIR(buf.st_mode))
		|| (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode) && flags->d));
}

int	is_dd_or_no_args(int argc, char **argv, int i)
{
	return (argv[1] == NULL || (i > 1 && argv[i] == NULL)
		|| (ft_strcmp(argv[i], "--") == 0 && argv[i + 1] == NULL)
		|| (ft_strcmp(argv[i], "--") == 0 && argc - i <= 1));
}

int	find_letter(char c, char *letters)
{
	int	index;

	index = 0;
	while (letters[index])
	{
		if (letters[index] == c)
			return (index);
		index++;
	}
	return (index);
}

int	get_flags(char **argv, t_info *flags)
{
	int		i;
	int		k;

	initialize_flags(flags);
	k = 1;
	i = 1;
	while (argv[i] && argv[i][0] == '-'
		&& argv[i][1] && ft_strcmp(argv[i], "--") != 0)
	{
		while (argv[i][k] != '\0')
			(void)g_flags[find_letter(argv[i][k++], FLAGS)](flags, argv[i]);
		k = 1;
		i++;
	}
	return (i);
}


