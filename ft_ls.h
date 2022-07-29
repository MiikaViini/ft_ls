/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/29 23:13:38 by mviinika         ###   ########.fr       */
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

# define FLAGS "lRart"
/* Defining permission strings */
# define RDWR
# define WR
# define RDWREX
# define RDEX
# define EX
# define WREX
# define NOPER

typedef struct s_fileinfo
{
	int			links;
	char		*perms;
	char		*m_time;
	char		*owner;
	char		*owner_gr;
	long long	size;
	char		*filename;
	int			stat_us;
	char		*path;
	int			total;
	int			index;
	long long	time_i;
}				t_fileinfo;

typedef struct s_dirs
{
	char		*dirs;
	char		*time;
	long long	time_i;
	int			depth;
}			t_dirs;

typedef struct s_flags
{
	int		l;
	int		cap_r;
	int		a;
	int		r;
	int		t;
	int		filecount;
}			t_flags;
typedef enum e_months
{
	Jan,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
}		t_months;
// typef enum flag_i
// {
// 	l,
// 	R,
// 	a,
// 	r,
// 	t
// }

t_fileinfo		*get_info(struct stat buf, char *path, int pathlen);
char			*permissions(int modes, struct stat buf);
//t_fileinfo	**line_array(char *argv, int index);
t_fileinfo		**alphabetical(t_fileinfo **info);
void			print_arr(t_fileinfo **linearray, t_flags *flags);
void			recursively(char *path, t_fileinfo **linearray, t_flags *flags);
t_fileinfo		**line_array(char *argv, t_fileinfo **linearray);
	// int			find_letter(char c, char *letters);

void			l_flag(t_flags *flags, char *string);
void			rec_flag(t_flags *flags, char *string);
void			a_flag(t_flags *flags, char *string);
void			r_flag(t_flags *flags, char *string);
void			t_flag(t_flags *flags, char *string);
//char		get_filetype(int modes, struct stat buf);
void			not_found(t_flags *flags, char *string);
void			alphabetical_s(t_dirs **dirs);
void			sort_time_r(t_dirs **dirs);
typedef void	(*t_fl)(t_flags *flags, char *string);
void			sort_time(t_fileinfo **linearray);
void			sort_depth_r(t_dirs **dirs);
void			sort_recu_r(t_dirs **dirs);
t_fileinfo			**ft_opendir( char *dirname, t_fileinfo **linearray, t_flags *flags, int f_count);

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
