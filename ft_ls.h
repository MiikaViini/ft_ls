/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/14 19:08:27 by mviinika         ###   ########.fr       */
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

# define FLAGS "lRart"

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
}				t_fileinfo;

typedef struct s_flags
{
	int		l;
	int		cap_r;
	int		a;
	int		r;
	int		t;
}			t_flags;

// typef enum flag_i
// {
// 	l,
// 	R,
// 	a,
// 	r,
// 	t
// }


t_fileinfo	*get_info(struct stat buf, char *path, int pathlen);
char		*permissions(int modes);
//t_fileinfo	**line_array(char *argv, int index);
t_fileinfo	**alphabetical(t_fileinfo **info);
void		print_arr(t_fileinfo **linearray);
void		recursively(char *dirname, t_fileinfo **linearray);
t_fileinfo	**line_array(char *argv, t_fileinfo **linearray);
	// int			find_letter(char c, char *letters);

void	l_flag(t_flags *flags, char *string);
void	rec_flag(t_flags *flags, char *string);
void	a_flag(t_flags *flags, char *string);
void	r_flag(t_flags *flags, char *string);
void	t_flag(t_flags *flags, char *string);
void	not_found(t_flags *flags, char *string);
typedef void	(*t_fl)(t_flags *flags, char *string);



static const t_fl g_flags[6] = {
	l_flag,
	rec_flag,
	a_flag,
	r_flag,
	t_flag,
	not_found
};
#endif
