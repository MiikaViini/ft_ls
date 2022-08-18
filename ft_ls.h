/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/18 19:39:47 by mviinika         ###   ########.fr       */
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
# include <sys/xattr.h>
# include <sys/acl.h>

# define FLAGS "lRartfAd"
# define SIX_MONTHS 15778476

typedef struct s_fileinfo
{
	int					links;
	char				*perms;
	char				m_time[25];
	char				*owner;
	char				*owner_gr;
	long long			size;
	char				filename[MAXNAMLEN];
	char				link[255];
	int					blocks;
	long long			time_m;
	long long			time_a;
	long long			biggest;
	int					longest_link;
	unsigned int		minor;
	unsigned int		major;
}					t_fileinfo;

typedef struct s_padds
{
	int			longest_fname;
	int			longest_oname;
	int			longest_ogroup;
	int			most_links;
	size_t		int_len;
	int			filename_len;
	int			ownername_len;
	int			groupname_len;
}				t_padds;

typedef struct s_flags
{
	int		l;
	int		cap_r;
	int		cap_a;
	int		a;
	int		r;
	int		t;
	int		f;
	int		d;
	int		filecount;
	int		no_flags;
	int		one_file;
	int		blocks;
	int		haslink;
}			t_flags;

/*********/
/**FLAGS**/
/*********/
void		l_flag(t_flags *flags, char *string);
void		rec_flag(t_flags *flags, char *string);
void		a_flag(t_flags *flags, char *string);
void		r_flag(t_flags *flags, char *string);
void		t_flag(t_flags *flags, char *string);
void		f_flag(t_flags *flags, char *string);
void		d_flag(t_flags *flags, char *string);
void		cap_a_flag(t_flags *flags, char *string);
void		not_found(t_flags *flags, char *string);
int			find_letter(char c, char *letters);
int			get_flags(char **argv, t_flags *flags);

/***********/
/**SORTING**/
/***********/
t_fileinfo	**alphabetical(t_fileinfo **info);
void		sort_time(t_fileinfo **linearray);
void		sort_time_a(t_fileinfo **linearray);
t_fileinfo	**sort_handler(t_fileinfo **linearray, t_flags *flags);

char		**arg_sort_handler(char **argv, int i, t_flags *flags);
void		sort_args_time(char **argv, int i);
void		ft_strarrrev(char **arr, int start);
int			move_index(char **arr, int start);

/*********************************************/
/**ERROR HANDLING, INITIALIZATION AND MEMORY**/
/*********************************************/
void		initialize_padds(t_padds *padds);
void		free_linearray(t_fileinfo **linearray);
void		initialize_info_struct(t_fileinfo *line);
void		initialize_flags(t_flags *flags);
void		print_flag_err(t_flags *flags, char c);
void		print_err(char *dirname, int error);

/********************/
/**ARGUMENT PARSING**/
/********************/
int			ft_ls(int argc, char **argv);
int			is_single_arg(int argc, char *path, int i);
int			is_single_file(struct stat buf, char **argv, int i, t_flags *flags);
int			is_dd_or_no_args(int argc, char **argv, int i);
void		path_maker(char *dest, char *dirname);
int			newpath(char *path, char **argv, int i);

/***********************************/
/**OPEN, READ, SAVE AND PRINT INFO**/
/***********************************/
t_fileinfo	**open_dir( char *dirname, t_fileinfo **linearray,
				t_flags *flags, int f_count);
t_fileinfo	*get_info(struct stat buf, char *path, int pathlen);
char		*permissions(int modes, struct stat buf, char *path);
void		print_arr(t_fileinfo **linearray, t_flags *flags);
void		recursively(char *path, t_fileinfo **linearray, t_flags *flags);
int			needs_newline(struct stat buf, char **argv, int i);
typedef void		(*t_fl)(t_flags *flags, char *string);
/**************/
/**JUMPTABLES**/
/**************/
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

static const t_fl	g_flags[9] = {
	l_flag,
	rec_flag,
	a_flag,
	r_flag,
	t_flag,
	f_flag,
	cap_a_flag,
	d_flag,
	not_found
};
#endif
