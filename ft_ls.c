/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/21 12:55:12 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	single_file(struct stat buf, char **argv, int *i, t_info *flags)
{
	t_fileinfo	**linearray;
	int			k;

	k = 0;
	flags->one_file++;
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo));
	if (!linearray)
		return ;
	while ((argv[*i] && lstat(argv[*i], &buf) != -1 && !S_ISDIR(buf.st_mode))
		|| (argv[*i] && lstat(argv[*i], &buf) != -1
			&& S_ISDIR(buf.st_mode) && flags->d))
	{
		linearray[k] = get_info(buf, argv[*i], 0, flags);
		if (linearray[k] == NULL)
			return ;
		k++;
		*i += 1;
	}
	linearray[k] = NULL;
	print_arr(sort_handler(linearray, flags), flags);
	if (lstat(argv[*i], &buf) != -1 && S_ISDIR(buf.st_mode))
		write(1, "\n", 1);
	free_linearray(linearray);
	flags->one_file = 0;
	*i -= 1;
}

static void	single_arg(char *path, t_fileinfo **linearray, t_info *flags)
{
	struct stat	buf;
	int			i;

	i = 0;
	if (lstat(path, &buf) == 0 && !S_ISDIR(buf.st_mode))
	{
		if (lstat(path, &buf) == -1)
		{
			print_err(path, errno);
			return ;
		}
		single_file(buf, &path, &i, flags);
	}
	else if (flags->cap_r)
		recursively(path, linearray, flags);
	else
	{
		linearray = open_dir(path, linearray, flags, 0);
		print_arr(linearray, flags);
		free_linearray(linearray);
	}
}

static int	multi_args(char **argv, t_info *flags,
							t_fileinfo **linearray, int i)
{
	char		path[PATH_MAX];
	struct stat	buf;

	ft_memset(path, '\0', PATH_MAX);
	arg_sort_handler(argv, i, flags);
	while (argv[i])
	{
		ft_strcpy(path, argv[i]);
		if (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode) && !flags->d)
			ft_printf("%s:\n", argv[i]);
		if (flags->cap_r && lstat(argv[i], &buf) != -1
			&& S_ISDIR(buf.st_mode) && !flags->d)
			recursively(path, linearray, flags);
		else if (is_single_file(buf, argv, i, flags))
			single_file(buf, argv, &i, flags);
		else
			linearray = open_dir(path, linearray, flags, 0);
		print_arr(linearray, flags);
		if (needs_newline(buf, argv, i++))
			write(1, "\n", 1);
		free_linearray(linearray);
	}
	return (0);
}

int	ft_ls(int argc, char **argv)
{
	t_fileinfo	**linearray;
	t_info		*info;
	char		path[PATH_MAX];
	int			i;

	i = 1;
	linearray = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (-1);
	i = get_flags(argv, info);
	ft_memset(path, '\0', PATH_MAX);
	if (is_dd_or_no_args(argc, argv, i))
		path[0] = '.';
	else
		ft_strcat(path, argv[i]);
	i = newpath(path, argv, i);
	if (is_single_arg(argc, path, i))
		single_arg(path, linearray, info);
	else
		multi_args(argv, info, linearray, i);
	free(info);
	return (0);
}

int	main(int argc, char **argv)
{
	// get_tty();
	// exit(1);
	ft_ls(argc, argv);
	return (0);
}
