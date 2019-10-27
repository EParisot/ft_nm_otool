/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_swaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:26:13 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/27 14:08:07 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static uint8_t	*get_cpu(void)
{
	static u_int8_t	cpu = 0;

	return (&cpu);
}

void			set_cpu(u_int8_t cpu)
{
	*get_cpu() = cpu;
}

uintmax_t		cpu_32(uintmax_t n)
{
	uint8_t	cpu;

	cpu = *get_cpu();
	if (cpu != 0)
		return (swap_32(n));
	return (n);
}

uintmax_t		cpu_64(uintmax_t n)
{
	uint8_t	cpu;

	cpu = *get_cpu();
	if (cpu != 0)
		return (swap_64(n));
	return (n);
}
