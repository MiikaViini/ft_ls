/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:31:15 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/16 15:44:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void ft_strarrrev(char **arr, int start)
{
	int 	len;
	char 	*temp;
	int 	i;

	i = start;
	temp = NULL;
	len = start;
	while(arr[start++])
		len++;
	len += i;
	while(i < len / 2)
	{
		temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
		i++;
	}
}

static void	validate_args(char **argv, int i, t_flags *flags)
{
	int 		start;
	char 		*temp;
	struct stat buf;

	start = i;
	while (argv[i] && argv[i + 1])
	{
		if (lstat(argv[i], &buf) != -1 && lstat(argv[i + 1], &buf) == -1) //&& ft_strcmp(argv[i], temp)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = start - 1;
		}
		i++;
	}
	i = start;
	while (flags->r && argv[i] && argv[i + 1])
	{
		if (lstat(argv[i + 1], &buf) < 0 && lstat(argv[i], &buf) < 0
			&& ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = start - 1;
		}
		i++;
	}
}

static void	sort_files_in_args(char **argv, int i, t_flags *flags)
{
	int 	int_temp;
	char 	*temp;
	struct	stat buf;

	temp = NULL;
	(void)flags;
	while (argv[i] && lstat(argv[i], &buf) < 0)
		i++;
	int_temp = i;
	while(argv[i])
	{
		if (lstat(argv[i], &buf) != -1 && !S_ISDIR(buf.st_mode) && lstat(argv[i - 1], &buf) != -1 && S_ISDIR(buf.st_mode))
		{
			temp = argv[i];
			argv[i] = argv[i - 1];
			argv[i - 1] = temp;
			i = int_temp;
		}
		i++;
	}
}

// void sort_args_atime(char **argv, int i, t_flags *flags)
// {
// 	int 	int_temp;
// 	char 	*temp;
// 	struct	stat buf;
// 	struct	stat buf2;

// 	temp = NULL;
// 	(void)flags;
// 	int_temp = i;
// 	while(argv[i] && argv[i + 1])
// 	{
// 		lstat(argv[i], &buf);
// 		lstat(argv[i + 1], &buf);
// 		if (buf.st_mtimespec.tv_nsec < buf2.st_mtimespec.tv_nsec)
// 		{
// 			temp = argv[i];
// 			argv[i] = argv[i + 1];
// 			argv[i + 1] = temp;
// 			i = int_temp;
// 		}
// 		i++;
// 	}
// }

// void sort_args_time(char **argv, int i, t_flags *flags)
// {
// 	int 	int_temp;
// 	char 	*temp;
// 	struct	stat buf;
// 	struct	stat buf2;

// 	temp = NULL;
// 	(void)flags;
// 	while (argv[i] && lstat(argv[i], &buf) < 0)
// 		i++;
// 	int_temp = i;
// 	while(argv[i] && argv[i + 1])
// 	{
// 		lstat(argv[i], &buf);
// 		lstat(argv[i + 1], &buf);
// 		if (buf.st_mtimespec.tv_sec < buf2.st_mtimespec.tv_sec)
// 		{
// 			temp = argv[i];
// 			argv[i] = argv[i + 1];
// 			argv[i + 1] = temp;
// 			i = int_temp;
// 		}
// 		i++;
// 	}
// 	sort_args_atime(argv, int_temp, flags);
// }

char **sort_args(char **argv, int i, t_flags *flags)
{
	int start;
	char *temp;
	struct stat buf;
	int		has_dirs;

	start = i;
	temp = NULL;
	has_dirs = 0;
	while (argv[i] && argv[i + 1])
	{
		if (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
			has_dirs++;
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = start - 1;
		}
		i++;
	}
	if (flags->t && !flags->f)
		sort_args_time(argv, start, flags);
	// i = 0;
	// i = 0;
	// while(argv[i])
	// 	printf("files %s\n", argv[i++]);
	//exit(1);
	if (flags->r && !flags->f)
		ft_strarrrev(argv, start);

	// i = 0;
	// while(argv[i])
	// 	printf("files %s\n", argv[i++]);
	//exit(1);
	validate_args(argv, start, flags);
	if (has_dirs)
		sort_files_in_args(argv, start, flags);
	// i = 0;
	// while(argv[i])
	// 	printf("validation %s\n", argv[i++]);


	return (argv);
}
