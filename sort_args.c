/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:31:15 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/28 19:46:41 by mviinika         ###   ########.fr       */
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

static void	sort_files(char **argv, int i, int *start, t_info *flags)
{
	char		*temp;
	struct stat	buf;

	temp = NULL;
	while (argv[i] && lstat(argv[i], &buf) < 0)
		i++;
	*start = i;
	while (argv[i] && argv[i + 1])
	{
		if (treated_like_file(argv[i], flags) == 1
			&& treated_like_file(argv[i + 1], flags) == 2)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = *start - 1;
		}
		i++;
	}
}

static void	sort_args_lex(char **argv, int i)
{
	int			start;
	char		*temp;

	start = i;
	temp = NULL;
	while (argv[i] && argv[i + 1])
	{
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
	int	start;

	start = i;
	if (!flags->f)
		sort_args_lex(argv, i);
	validate_args(argv, i, &start);
	sort_files(argv, i, &start, flags);
	sort_args_time(argv, i, flags);
	if (flags->r && !flags->f)
		ft_strarrrev(argv, start);
	return (argv);
}
