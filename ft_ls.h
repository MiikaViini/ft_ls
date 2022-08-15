/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/15 14:11:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <errno.h>
# include <time.h>
# include <limits.h>
# include <sys/ioctl.h>

# define FLAGS "lRart"
/* Defining permission strings */
# define RDWR
# define WR
# define RDWREX
# define RDEX
# define EX
# define WREX
# define NOPER

# define SIX_MONTHS 15778476

typedef struct s_fileinfo
{
	int			links;
	char		*perms;
	char		m_time[25];
	char		*owner;
	char		*owner_gr;
	long long	size;
	char		filename[MAXNAMLEN];
	char		link[256];
	int			stat_us;
	int			blocks;
	int			index;
	long long	time_m;
	long long	time_a;
	long		inode;
	long long	biggest;
	int			longest_link;
	unsigned int		minor;
	unsigned int		major;
}				t_fileinfo;

typedef struct s_flags
{
	int		l;
	int		cap_r;
	int		a;
	int		r;
	int		t;
	int		filecount;
	int		no_flags;
	int		one_file;
	int		blocks;
	int		haslink;
}			t_flags;

t_fileinfo		*get_info(struct stat buf, char *path, int pathlen);
char			*permissions(int modes, struct stat buf);
void			print_arr(t_fileinfo **linearray, t_flags *flags);
void			recursively(char *path, t_fileinfo **linearray, t_flags *flags);
t_fileinfo		**line_array(char *argv, t_fileinfo **linearray);
/*
** Flags
*/
void			l_flag(t_flags *flags, char *string);
void			rec_flag(t_flags *flags, char *string);
void			a_flag(t_flags *flags, char *string);
void			r_flag(t_flags *flags, char *string);
void			t_flag(t_flags *flags, char *string);
void			not_found(t_flags *flags, char *string);

typedef void	(*t_fl)(t_flags *flags, char *string);
t_fileinfo		**sort_handler(t_fileinfo **linearray, t_flags *flags);
void			sort_time(t_fileinfo **linearray);
void			sort_time_a(t_fileinfo **linearray);
t_fileinfo		**alphabetical(t_fileinfo **info);
void			path_maker(char *dest, char *dirname);
t_fileinfo		**ft_opendir( char *dirname, t_fileinfo **linearray, t_flags *flags, int f_count);
void			print_err(char *dirname, int error);
void 			free_linearray(t_fileinfo **linearray);
void 			initialize_info_struct(t_fileinfo *line);
void 			initialize_flags(t_flags *flags);
int 			find_letter(char c, char *letters);
char **sort_args(char **argv, int i, t_flags *flags);
int is_single_arg(int argc, char *path, int i);
int is_single_file(struct stat buf, char **argv, int i);
int is_dd_or_no_args(int argc, char **argv, int i);

//int ft_ls(int argc, char **argv);

static const char	g_perms[8][4] = {
"---",
"--x",
"-w-",
"-wx",
"r--",
"r-x",
"rw-",
"rwx"
};

static const t_fl	g_flags[6] = {
	l_flag,
	rec_flag,
	a_flag,
	r_flag,
	t_flag,
	not_found
};
#endif
