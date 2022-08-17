/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:31:15 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/17 12:53:10 by mviinika         ###   ########.fr       */
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

void sort_args_time(char **argv, int i, t_flags *flags)
{
	int 	int_temp;
	char 	*temp;
	struct	stat buf;
	struct stat buf2;
	int		stat;

	temp = NULL;
	(void)flags;
	//stat = lstat(argv[i], &buf);
	// printf("%s\n", argv[i]);
	// exit(1);
	// while(argv[i])
	// 	printf("%s\n", argv[i++]);
	// exit(1);
	while (argv[i])
	{
		stat = lstat(argv[i], &buf);
		printf("%s %d\n", argv[i], stat);
		if(stat == -1 || !S_ISDIR(buf.st_mode))
			i++;
		else
			break;
	}
	// while(argv[i])
	// 	printf("%s\n", argv[i++]);
	// exit(1);
	int_temp = i;
	while(argv[i] && argv[i + 1])
	{
		lstat(argv[i], &buf);
		lstat(argv[i + 1], &buf2);
		if (buf2.st_mtimespec.tv_sec > buf.st_mtimespec.tv_sec)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = int_temp - 1;
		}
		i++;
	}
	if (flags->r && !flags->f)
		ft_strarrrev(argv, int_temp);
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
	if (flags->t && !flags->f)
		sort_args_time(argv, int_temp, flags);

}

void sort_args_atime(char **argv, int i, t_flags *flags)
{
	int 	int_temp;
	char 	*temp;
	struct	stat buf;
	struct	stat buf2;

	temp = NULL;
	(void)flags;
	lstat(argv[i], &buf);
	while (argv[i] && !S_ISDIR(buf.st_mode))
	{
		lstat(argv[i++], &buf);
	}

	int_temp = i;
	while(argv[i] && argv[i + 1])
	{
		lstat(argv[i], &buf);
		lstat(argv[i + 1], &buf2);
		printf("%s %ld\n", argv[i],buf2.st_mtimespec.tv_nsec);
		printf("%s %ld\n",argv[i + 1],  buf.st_mtimespec.tv_nsec);
		if (buf2.st_mtimespec.tv_nsec < buf.st_mtimespec.tv_nsec)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			i = int_temp - 1;
		}
		i++;
	}
}



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

	// i = 0;
	// i = 0;
	// while(argv[i])
	// 	printf("files %s\n", argv[i++]);
	//exit(1);


	// i = 0;
	// while(argv[i])
	// 	printf("files %s\n", argv[i++]);
	//exit(1);

	validate_args(argv, start, flags);
	if (has_dirs)
		sort_files_in_args(argv, start, flags);

	return (argv);
}
