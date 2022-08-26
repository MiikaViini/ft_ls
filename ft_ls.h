/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/26 23:46:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
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
# include <sys/ioctl.h>

# define FLAGS "lRartfAdn1"
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
	long long			time_m;
	long long			time_a;
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
	long long	biggest;
	int			longest_link;
}				t_padds;

typedef struct s_info
{
	int		l;
	int		cap_r;
	int		cap_a;
	int		cap_f;
	int		one;
	int		a;
	int		r;
	int		t;
	int		f;
	int		d;
	int		n;
	int		one_file;
	int		blocks;
	int		f_count;
}			t_info;

typedef struct s_mc_val
{
	int		width;
	int		max_cols;
	int		max_rows;
	int		x;
	int		y;
	char	c;
}			t_mc_val;

/*********/
/**FLAGS**/
/*********/
void		l_flag(t_info *flags, char *string);
void		rec_flag(t_info *flags, char *string);
void		a_flag(t_info *flags, char *string);
void		r_flag(t_info *flags, char *string);
void		t_flag(t_info *flags, char *string);
void		f_flag(t_info *flags, char *string);
void		d_flag(t_info *flags, char *string);
void		cap_a_flag(t_info *flags, char *string);
void		cap_g_flag(t_info *flags, char *string);
void		n_flag(t_info *flags, char *string);
void		one_flag(t_info *flags, char *string);
void		not_found(t_info *flags, char *string);
int			find_letter(char c, char *letters);
int			get_flags(char **argv, t_info *flags);

/***********/
/**SORTING**/
/***********/
t_fileinfo	**sort_lexico(t_fileinfo **info);
void		sort_time(t_fileinfo **linearray);
void		sort_time_a(t_fileinfo **linearray);
t_fileinfo	**sort_handler(t_fileinfo **linearray, t_info *flags);
char		**arg_sort_handler(char **argv, int i, t_info *flags);
void		sort_args_time(char **argv, int i);
void		ft_strarrrev(char **arr, int start);
int			move_index(char **arr, int start);
void		swap_line(t_fileinfo **linearray, int i, int j, t_fileinfo *temp);
int			treated_like_file(char *str, t_info *flags);

/*********************************************/
/**ERROR HANDLING, INITIALIZATION AND MEMORY**/
/*********************************************/
void		initialize_padds(t_padds *padds);
void		initialize_mc_val(t_mc_val *values);
void		free_linearray(t_fileinfo **linearray);
void		initialize_info_struct(t_fileinfo *line);
void		initialize_flags(t_info *flags);
void		print_flag_err(t_info *flags, char c);
void		print_err(char *dirname, int error);

/********************/
/**ARGUMENT PARSING**/
/********************/
int			ft_ls(int argc, char **argv);
int			is_single_arg(int argc, char *path, int i);
int			is_single_file(struct stat buf, char **argv, int i, t_info *flags);
int			is_dd_or_no_args(int argc, char **argv, int i);
void		path_maker(char *dest, char *dirname, t_info *info);
int			newpath(char *path, char **argv, int i);

/***********************************/
/**OPEN, READ, SAVE AND PRINT INFO**/
/***********************************/
t_fileinfo	**open_dir( char *dirname, t_fileinfo **linearray,
				t_info *flags, int f_count);
t_fileinfo	*get_info(struct stat buf, char *path, int pathlen, t_info *info);
char		*permissions(int modes, struct stat buf, char *path);
void		print_arr(t_fileinfo **linearray, t_info *flags);
void		recursively(char *path, t_fileinfo **linearray, t_info *flags);
int			needs_newline(struct stat buf, char **argv, int i);
typedef void		(*t_fl)(t_info *flags, char *string);
int			print_multicolumn(t_info *info,
				t_fileinfo **linearray, t_padds *padds);

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

static const t_fl	g_flags[11] = {
	l_flag,
	rec_flag,
	a_flag,
	r_flag,
	t_flag,
	f_flag,
	cap_a_flag,
	d_flag,
	n_flag,
	one_flag,
	not_found
};
#endif
