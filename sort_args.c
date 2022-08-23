/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:31:15 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/23 16:11:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	validate_args(char **argv, int i)
{
	int			start;
	char		*temp;
	struct stat	buf;

	start = i;
	while (argv[i] && argv[i + 1])
	{
		if (lstat(argv[i], &buf) != -1 && lstat(argv[i + 1], &buf) == -1)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = start - 1;
		}
		i++;
	}
}

// static void	set_files_range(char **argv, int start)
// {
// 	int i;

// 	i = 0;
// 	struct stat	buf;

// 	while (argv[*start] ) //&& lstat(argv[*start], &buf) && !S_ISDIR(buf.st_mode)
// 	{
// 		ft_printf("%s\n", argv[*start]);
// 		*start = *start + 1;
// 		//*end = *end + 1;
// 	}
		
// 	s_2 = end;
// }

static void	sort_files_in_args(char **argv, int i, t_info *flags)
{
	int			start;
	char		*temp;
	struct stat	buf;

	temp = NULL;
	while (argv[i] && lstat(argv[i], &buf) < 0)
		i++;
	start = i;
	while (argv[i])
	{
		if (lstat(argv[i], &buf) != -1 && !S_ISDIR(buf.st_mode)
			&& lstat(argv[i - 1], &buf) != -1 && S_ISDIR(buf.st_mode))
		{
			temp = argv[i];
			argv[i] = argv[i - 1];
			argv[i - 1] = temp;
			i = start;
		}
		i++;
	}
	// set_files_range(argv, start);
	if (flags->r && !flags->f)
		ft_strarrrev(argv, start);
	// ft_printf("%d\n",end);
	// ft_printf("%d\n", s_2);
	// // while (end > s_2)
	// {
	// 	ft_printf("%s\n", argv[s_2++]);
	// }
	// exit(1);
}

static void	sort_args_lex(char **argv, int i, int *has_dirs, t_info *flags)
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
	if (flags->r)
		ft_strarrrev(argv, start);
}

char	**arg_sort_handler(char **argv, int i, t_info *flags)
{
	int	has_dirs;

	has_dirs = 0;
	if (!flags->f)
		sort_args_lex(argv, i, &has_dirs, flags);
	validate_args(argv, i);
	if (has_dirs)
		sort_files_in_args(argv, i, flags);
	if (flags->t && !flags->f)
		sort_args_time(argv, i, flags);
	// if (flags->r && !flags->f)
	// 	ft_strarrrev(argv, i);
	while(argv[i])
		ft_printf("%s\n", 	argv[i++]);
	exit(1);
	return (argv);
}
