/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:41:12 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/20 20:16:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	n_flag(t_info *flags, char *string)
{
	(void)string;
	flags->n = 1;
	flags->l = 1;
}

void	cap_g_flag(t_info *flags, char *string)
{
	(void)string;
	flags->cap_g = 1;
}
