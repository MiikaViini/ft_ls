/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:24:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/31 18:04:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void	f_flag(t_info *flags, char *string)
{
	(void)string;
	flags->f = 1;
}

void	cap_a_flag(t_info *flags, char *string)
{
	(void)string;
	flags->cap_a = 1;
}

void	d_flag(t_info *flags, char *string)
{
	(void)string;
	flags->d = 1;
}

void	n_flag(t_info *flags, char *string)
{
	(void)string;
	flags->n = 1;
	flags->l = 1;
}

void	one_flag(t_info *flags, char *string)
{
	(void)string;
	flags->one = 1;
	flags->l = 0;
}
