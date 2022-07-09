/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:03:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/09 21:09:09 by mviinika         ###   ########.fr       */
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
}				t_fileinfo;

typedef struct s_flags
{
	int		l;
	int		cap_r;
	int		a;
	int		r;
	int		t;
}			t_flags;

t_fileinfo	*get_info(struct stat buf, char *path, int pathlen);
char		*permissions(int modes);
t_fileinfo	**line_array(int argc, char **argv);
t_fileinfo	**alphabetical(t_fileinfo **info);

#endif
