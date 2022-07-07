/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:02:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/07 18:29:14 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>

typedef struct s_fileinfo
{
	int			links;
	char		*perms;
	char		*m_time;
	char		*owner;
	char		*owner_gr;
	long long	size;
	char		*filename;
}				t_fileinfo;

char	*ft_itoa(int n);
char	*ft_itoabase(unsigned long long int num, int base, int flag);
char	*ft_strnew(size_t size);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t size);
char	*ft_strdup(const char *s);

char	*permissions(int modes)
{
	char *perm;
	int i;
	char *mode;
	int counter;

	counter = 3;
	mode = ft_itoabase(modes, 8, 0);
	i = 0;
	perm = ft_strnew(10);
	while(*mode)
	{
		if (*mode == '4' && mode)
		{
			perm[i++] = 'd';
			mode += 2;
			while(*mode >= '0' && *mode <= '7')
			{
				if (*mode == '0')
				{
					while(counter > 0)
					{
						perm[i++] = '-';
						counter--;
					}
				}

				else if(*mode == '1')
				{
					perm[i++] = '-';
					perm[i++] = '-';
					perm[i++]= 'x';
				}

				else if (*mode == '2')
				{
					perm[i++] = '-';
					perm[i++] = 'w';
					perm[i++] = '-';
				}

				else if (*mode == '3')
				{
					perm[i++] = '-';
					perm[i++] = 'w';
					perm[i++] = 'x';
				}

				else if (*mode == '4')
				{
					perm[i++] = 'r';
					perm[i++] = '-';
					perm[i++] = '-';

				}

				else if (*mode == '5')
				{
					perm[i++] = 'r';
					perm[i++] = '-';
					perm[i++] = 'x';
				}

				else if (*mode == '6')
				{
					perm[i++] = 'r';
					perm[i++] = 'w';
					perm[i++] = '-';
				}

				else if (*mode == '7')
				{
					perm[i++] = 'r';
					perm[i++] = 'w';
					perm[i++] = 'x';
				}
				counter = 3;
				mode++;
			}
		}

		else if (*mode == '1' && mode)
		{
			perm[i++] = '-';
			mode += 3;
			while(*mode >= '0' && *mode <= '7')
			{
				if (*mode == '0')
				{
					while(counter > 0)
					{
						perm[i++] = '-';
						counter--;
					}
				}

				else if(*mode == '1')
				{
					perm[i++] = '-';
					perm[i++] = '-';
					perm[i++]= 'x';
				}

				else if (*mode == '2')
				{
					perm[i++] = '-';
					perm[i++] = 'w';
					perm[i++] = '-';
				}

				else if (*mode == '3')
				{
					perm[i++] = '-';
					perm[i++] = 'w';
					perm[i++] = 'x';
				}

				else if (*mode == '4')
				{
					perm[i++] = 'r';
					perm[i++] = '-';
					perm[i++] = '-';

				}

				else if (*mode == '5')
				{
					perm[i++] = 'r';
					perm[i++] = '-';
					perm[i++] = 'x';
				}

				else if (*mode == '6')
				{
					perm[i++] = 'r';
					perm[i++] = 'w';
					perm[i++] = '-';
				}

				else if (*mode == '7')
				{
					perm[i++] = 'r';
					perm[i++] = 'w';
					perm[i++] = 'x';
				}
				mode++;
				counter = 3;
			}
		}
	}
	return (perm);
}

t_fileinfo	*get_info(struct stat buf, struct dirent *dirp)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*time;
	t_fileinfo			*line;

	line = malloc(sizeof(t_fileinfo));
	time = ft_strnew(35);
	stat(dirp->d_name, &buf);
	ft_strcpy(time, ctime(&buf.st_mtime));
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	line->owner = ft_strdup(pwd->pw_name);
	line->owner_gr = ft_strdup(grp->gr_name);
	line->links = buf.st_nlink;
	line->size = buf.st_size;
	line->filename =ft_strdup(dirp->d_name);
	line->perms = permissions(buf.st_mode);
	line->m_time = time;
	return (line);
}

t_fileinfo	**line_array(int argc, char **argv)
{
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;
	t_fileinfo		*info[500];
	int				i;

	// Open and read
	//info = (t_fileinfo **)malloc(sizeof(t_fileinfo));
	dp = opendir(argv[1]);
	dirp = readdir(dp);
	i = 0;
	// Get info
	stat(dirp->d_name, &buf);
	while (dirp != NULL)
	{
		// info = malloc(sizeof(t_fileinfo));
		info[i] = get_info(buf, dirp);
		dirp = readdir(dp);
		stat(dirp->d_name, &buf);
		i++;
	}
	info[i] = NULL;
	closedir(dp);
	return (info);
}


int	main(int argc, char **argv)
{
	t_fileinfo **linearray;
	int	i;
	i = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: ./program directory_name\n");
		exit(EXIT_FAILURE);
	}
	linearray = line_array(argc, argv);
	while(linearray[i] != NULL)
	{
		printf("%3s ", linearray[i]->perms);
		printf("%3d ", linearray[i]->links);
		printf("%3s ", linearray[i]->owner);
		printf("%3s ", linearray[i]->owner_gr);
		printf("%5lld ", linearray[i]->size);
		printf("%.12s ", linearray[i]->m_time + 4);
		printf("%s\n", linearray[i]->filename);
		i++;
	}

	exit(EXIT_SUCCESS);
	return 0;
}

