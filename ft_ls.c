/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/31 18:04:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static void	single_file(struct stat buf, char **argv, int *i, t_info *flags)
{
	t_fileinfo	**linearray;
	int			k;

	k = 0;
	flags->one_file++;
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * flags->f_count + 1);
	if (!linearray)
	{
		flags->ret = 1;
		return ;
	}
	flags->f_count = 0;
	while (treated_like_file(argv[*i], flags) == 2)
	{
		linearray[k] = get_info(buf, argv[*i], 0, flags);
		if (linearray[k++] == NULL)
			break ;
		*i += 1;
		flags->f_count++;
	}
	linearray[k] = NULL;
	print_arr(sort_handler(linearray, flags), flags);
	needs_newline(buf, argv, *i, flags);
	free_linearray(linearray);
	*i -= 1;
}

static void	single_arg(char *path, t_fileinfo **linearray, t_info *flags)
{
	struct stat	buf;
	int			i;
	int			i_stat;

	i = 0;
	flags->one_file = 0;
	i_stat = stat(path, &buf);
	if (treated_like_file(path, flags) == 2)
		single_file(buf, &path, &i, flags);
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
		flags->one_file = 0;
		ft_strcpy(path, argv[i]);
		lstat(path, &buf);
		if (treated_like_file(path, flags) == 1)
			ft_printf("%s:\n", argv[i]);
		if (flags->cap_r && treated_like_file(path, flags) == 1)
			recursively(path, linearray, flags);
		else if (treated_like_file(path, flags) == 2)
			single_file(buf, argv, &i, flags);
		else
			linearray = open_dir(path, linearray, flags, 0);
		print_arr(linearray, flags);
		if (needs_newline(buf, argv, i++, flags))
			write(1, "\n", 1);
		free_linearray(linearray);
	}
	return (0);
}

int	ft_ls(int argc, char **argv, t_info *info)
{
	t_fileinfo	**linearray;
	char		path[PATH_MAX];
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	linearray = NULL;
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
	ret = info->ret;
	return (ret);
}

int	main(int argc, char **argv)
{
	int			ret;
	t_info		*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (1);
	ret = ft_ls(argc, argv, info);
	free(info);
	return (ret);
}
