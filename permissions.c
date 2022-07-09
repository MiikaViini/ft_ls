/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:30:25 by mviinika          #+#    #+#             */
/*   Updated: 2022/07/09 20:30:42 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
