/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/15 17:42:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int get_flags(char **argv, t_flags *flags)
{
	int i;
	int k;

	initialize_flags(flags);
	k = 1;
	i = 1;
	while (argv[i] && argv[i][0] == '-'
		&& argv[i][1] && ft_strcmp(argv[i], "--") != 0)
	{
		while (argv[i][k] != '\0')
			g_flags[find_letter(argv[i][k++], FLAGS)](flags, argv[i]);
		k = 1;
		i++;
	}
	return (i);
}

static void single_file(struct stat buf, char **argv, int i, t_flags *flags)
{
	t_fileinfo **linearray;

	flags->one_file++;
	linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 2);
	linearray[0] = get_info(buf, argv[i], 0);
	linearray[1] = NULL;
	print_arr(linearray, flags);
	free_linearray(linearray);
	flags->one_file = 0;
}

static int single_arg(char *path, t_fileinfo **linearray, t_flags *flags)
{
	struct stat buf;
	int		l_stat;

	l_stat = lstat(path, &buf);
	if (flags->cap_r)
	{
		recursively(path, linearray, flags);
		return (0);
	}
	else if (!S_ISDIR(buf.st_mode))
	{
		if (l_stat < 0)
		{
			print_err(path, errno);
			return (-1);
		}
		single_file(buf, &path, 0, flags);
	}
	else
	{
		linearray = ft_opendir(path, linearray, flags, 0);
		print_arr(linearray, flags);
		free_linearray(linearray);
	}
	return (0);
}

static int multi_args(char **argv, t_flags *flags, t_fileinfo **linearray, int i)
{
	char	path[PATH_MAX];
	struct 	stat buf;

	ft_memset(path, '\0', PATH_MAX);
	sort_args(argv, i, flags);
	while (argv[i])
	{
		if (argv[i])
			ft_strcpy(path, argv[i]);
		if (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
				ft_printf("%s:\n", argv[i]);
		if (flags->cap_r && lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
			recursively(path, linearray, flags);
		else if (is_single_file(buf, argv, i))
			single_file(buf, argv, i, flags);
		else
			linearray = ft_opendir(path, linearray, flags, 0);
		print_arr(linearray, flags);
		if (argv[++i] != NULL && lstat(argv[i], &buf) != -1
				&& S_ISDIR(buf.st_mode))
		write(1, "\n", 1);
		if (linearray)
			free_linearray(linearray);
	}
	return (0);
}

int newpath(char *path, char **argv, int i)
{
	if (argv[i] && ft_strcmp(argv[i], "--") == 0  && argv[i + 1] != NULL)
	{
		i++;
		ft_strcpy(path, argv[i]);
	}
	return i;
}

int ft_ls(int argc, char **argv)
{
	t_fileinfo 	**linearray;
	t_flags 	*flags;
	char 		path[PATH_MAX];
	int 		i;

	i = 1;
	linearray = NULL;
	flags = (t_flags *)malloc(sizeof(t_flags));
	i = get_flags(argv, flags);
	ft_memset(path, '\0', PATH_MAX);
	if (is_dd_or_no_args(argc, argv, i))
		path[0] = '.';
	else
		ft_strcat(path, argv[i]);
	i = newpath(path, argv, i);
	if (is_single_arg(argc, path, i))//argc == 1 || (argc == 2 && ft_strcmp(path, ".") == 0) || argc - i <= 1
		single_arg(path, linearray, flags);
	else
		multi_args(argv, flags, linearray, i);
	free(flags);
	return (0);
}

// argv[1] == NULL || (i > 1 && argv[i] == NULL)
// 		|| (ft_strcmp(argv[i], "--") == 0  && argv[i] == NULL)
// 		|| (ft_strcmp(argv[i], "--") == 0 && argc - i <= 1)

// sort_args(argv, i, flags);
// 		while (argv[i])
// 		{
// 			if (argv[i])
// 				ft_strcpy(path, argv[i]);
// 			if (lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
// 					ft_printf("%s:\n", argv[i]);
// 			if (flags->cap_r && lstat(argv[i], &buf) != -1 && S_ISDIR(buf.st_mode))
// 				recursively(path, linearray, flags);
// 			else if (lstat(argv[i], &buf) != -1 && !S_ISDIR(buf.st_mode))
// 			{
// 				flags->one_file++;
// 				linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 2);
// 				linearray[0] = get_info(buf, argv[i], 0);
// 				linearray[1] = NULL;
// 				print_arr(linearray, flags);

// 			}
// 			else
// 				ft_opendir(path, linearray, flags, 0);
// 			i++;
// 			if (argv[i] != NULL && lstat(argv[i], &buf) != -1
// 				 && S_ISDIR(buf.st_mode))
// 				write(1, "\n", 1);
// 		}

int main(int argc, char **argv)
{

	// t_fileinfo	**linearray;
	// t_flags		*flags;
	// struct stat		buf;
	// char		path[PATH_MAX];

		ft_ls(argc, argv);
	// exit(1);
	//  linearray = NULL;
	//  if (argv[1] && argv[1][i] == '-')
	//  {
	//  	while (argv[1][++i] != '\0')
	//  		g_flags[find_letter(argv[1][i], FLAGS)](flags, argv[1]);
	//  	if (argc >= 3)
	//  	{
	//  		while (arg_count < argc)
	//  		{
	//  			if (lstat(argv[arg_count], &buf) < 0)
	//  				print_err(argv[arg_count], errno);
	//  			else if (!S_ISDIR(buf.st_mode))
	//  			{
	//  				flags->one_file = 1;
	//  				linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 2);
	//  				linearray[0] = get_info(buf, argv[arg_count], 0);
	//  				linearray[1] = NULL;
	//  				print_arr(linearray, flags);
	//  				free(linearray);
	//  			}
	//  			else if (flags->cap_r)
	//  				recursively(argv[arg_count], linearray, flags);
	//  			else
	//  				ft_opendir(argv[arg_count], linearray, flags, 0);
	//  			arg_count++;
	//  		}
	//  	}
	//  }
	//  else if (argc >= 1 && flags->no_flags)
	//  {
	//  	if (argc == 1)
	//  		ft_strcat(path, ".");
	//  	else
	//  		ft_strcat(path, argv[1]);
	//  	stat(path, &buf);
	//  	if (S_ISDIR(buf.st_mode))
	//  	{
	//  		ft_opendir(path, linearray, flags, 0);
	//  	}
	//  	else
	//  	{
	//  		linearray = (t_fileinfo **)malloc(sizeof(t_fileinfo) * 1);
	//  		linearray[0] = get_info(buf, path, 0);
	//  		print_arr(linearray, flags);
	//  	}
	//  }
	// free(linearray);
	// free(flags);
	return (0);
}


// t_fileinfo **line_array(char *argv, t_fileinfo **linearray)
// {
// 	DIR *dp;
// 	struct dirent *dirp;
// 	struct stat buf;
// 	int i;
// 	char *temp;
// 	char *path;

// 	temp = ft_strjoin(argv, "/");
// 	dp = opendir(temp);
// 	if (!dp || !temp)
// 		return (NULL);
// 	dirp = readdir(dp);
// 	i = 0;
// 	while (dirp != NULL)
// 	{
// 		path = ft_strjoin(temp, dirp->d_name);
// 		lstat(path, &buf);
// 		linearray[i++] = get_info(buf, path, ft_strlen(temp));
// 		dirp = readdir(dp);
// 	}
// 	linearray[i] = NULL;
// 	linearray = alphabetical(linearray);
// 	closedir(dp);
// 	return (linearray);
// }
