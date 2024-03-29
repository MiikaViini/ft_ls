/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:14:50 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/31 18:04:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

void	l_flag(t_info *flags, char *string)
{
	(void)string;
	flags->l = 1;
}

void	rec_flag(t_info *flags, char *string)
{
	(void)string;
	flags->cap_r = 1;
}

void	a_flag(t_info *flags, char *string)
{
	(void)string;
	flags->a = 1;
}

void	r_flag(t_info *flags, char *string)
{
	(void)string;
	flags->r = 1;
}

void	t_flag(t_info *flags, char *string)
{
	(void)string;
	flags->t = 1;
}
