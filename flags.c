/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:14:50 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/17 18:08:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void	l_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->l = 1;
}

void	rec_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->cap_r = 1;
}

void	a_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->a = 1;
}

void	r_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->r = 1;
}

void	t_flag(t_flags *flags, char *string)
{
	(void)string;
	flags->t = 1;
}

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
			break;
		}
		string++;
	}
	ft_printf("ft_ls: illegal option -- %c\nusage: ./ft_ls [-Raflrt] [file ...]\n", c);
	free(flags);
	exit(EXIT_FAILURE);
}
