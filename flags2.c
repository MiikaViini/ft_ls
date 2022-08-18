/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:24:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/18 19:22:48 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	f_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->f = 1;
}

void	cap_a_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->cap_a = 1;
}

void	d_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->d = 1;
}

void	not_found(t_flags *flags, char *string)
{
	char	c;

	c = '\0';
	string++;
	while (string)
	{
		if (!ft_strchr(FLAGS, *string))
		{
			c = *string;
			break ;
		}
		string++;
	}
	print_flag_err(flags, c);
}
