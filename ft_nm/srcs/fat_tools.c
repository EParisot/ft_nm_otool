/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:02:58 by eparisot          #+#    #+#             */
/*   Updated: 2020/01/07 15:15:34 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint32_t		c_compat_32(void *obj, uint32_t nf, void *end, char *filename)
{
	uint32_t			i;
	struct fat_arch		*fatarch;
	struct fat_header	*header;
	uint32_t			res;

	header = (struct fat_header *)obj;
	fatarch = (struct fat_arch *)(header + 1);
	i = -1;
	res = 0;
	while (++i < nf)
	{
		if (obj + swap_32(fatarch[i].offset) < end)
		{
			if (i == 0 && nf > 1 && swap_32(fatarch[i + 1].cputype) == \
							CPU_TYPE_X86_64)
				continue ;
			if (swap_32(fatarch[i].cputype) == CPU_TYPE_X86_64)
				res++;
		}
		else
			print_err("Error corrupted\n", filename);
	}
	return (res);
}

uint64_t		c_compat_64(void *obj, uint64_t nf, void *end, char *filename)
{
	uint64_t			i;
	struct fat_arch		*fatarch;
	struct fat_header	*header;
	uint64_t			res;

	header = (struct fat_header *)obj;
	fatarch = (struct fat_arch *)(header + 1);
	i = -1;
	res = 0;
	while (++i < nf)
	{
		if (obj + swap_64(fatarch[i].offset) < end)
		{
			if (i == 0 && nf > 1 && swap_64(fatarch[i + 1].cputype) == \
							CPU_TYPE_X86_64)
				continue ;
			if (swap_64(fatarch[i].cputype) == CPU_TYPE_X86_64)
				res++;
		}
		else
			print_err("Error corrupted\n", filename);
	}
	return (res);
}
