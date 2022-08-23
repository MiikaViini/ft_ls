/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:31:15 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/24 00:54:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	validate_args(char **argv, int i, int *start)
{
	char		*temp;
	struct stat	buf;

	*start = i;
	while (argv[i] && argv[i + 1])
	{
		if (lstat(argv[i], &buf) != -1 && lstat(argv[i + 1], &buf) == -1)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = *start - 1;
		}
		i++;
	}
}

static void	sort_files_in_args(char **argv, int i, int *start)
{
	char		*temp;
	struct stat	buf;

	temp = NULL;
	while (argv[i] && lstat(argv[i], &buf) < 0)
		i++;
	*start = i;
	while (argv[i])
	{
		if (lstat(argv[i], &buf) != -1 && !S_ISDIR(buf.st_mode)
			&& lstat(argv[i - 1], &buf) != -1 && S_ISDIR(buf.st_mode))
		{
			temp = argv[i];
			argv[i] = argv[i - 1];
			argv[i - 1] = temp;
			i = *start;
		}
		i++;
	}
}

static void	sort_args_lex(char **argv, int i, int *has_dirs)
{
	int			start;
	char		*temp;
	struct stat	buf;

	start = i;
	temp = NULL;
	while (argv[i] && argv[i + 1])
	{
		if (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
			*has_dirs = 1;
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = start - 1;
		}
		i++;
	}
}

char	**arg_sort_handler(char **argv, int i, t_info *flags)
{
	int	has_dirs;
	int	start;

	has_dirs = 0;
	start = i;
	if (!flags->f)
		sort_args_lex(argv, i, &has_dirs);
	validate_args(argv, i, &start);
	if (has_dirs)
		sort_files_in_args(argv, i, &start);
	if (flags->t && !flags->f)
		sort_args_time(argv, i);
	if (flags->r && !flags->f)
		ft_strarrrev(argv, start);
	return (argv);
}
