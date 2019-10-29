/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:25:27 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/29 10:32:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

int				print_err(char *err, char *arg)
{
	ft_putstr(err);
	if (ft_strlen(arg))
	{
		ft_putstr(" '");
		ft_putstr(arg);
		ft_putstr("'");
	}
	ft_putchar('\n');
	return (1);
}
