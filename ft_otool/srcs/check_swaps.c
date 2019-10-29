/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_swaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:26:13 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/29 11:32:12 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

uint8_t			*get_cpu(void)
{
	static u_int8_t	cpu = 0;

	return (&cpu);
}

void			set_cpu(u_int8_t cpu)
{
	*get_cpu() = cpu;
}

uint32_t		cpu_32(uint32_t n)
{
	uint8_t	cpu;

	cpu = *get_cpu();
	if (cpu != 0)
		return (swap_32(n));
	return (n);
}

uint64_t		cpu_64(uint64_t n)
{
	uint8_t	cpu;

	cpu = *get_cpu();
	if (cpu != 0)
		return (swap_64(n));
	return (n);
}
