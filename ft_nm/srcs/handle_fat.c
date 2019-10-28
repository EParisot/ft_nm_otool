/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:23:17 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/28 14:34:20 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			fat64_loop(void *obj, uint64_t nf, struct fat_arch *fatarch, \
																void *end)
{
	uint64_t		i;

	i = -1;
	while (++i < nf)
	{
		if (i == 0 && nf > 1)
			continue ;
		else if (obj + swap_64(fatarch[i].offset) < end)
		{
			if ((swap_64(fatarch[i].cputype) == CPU_TYPE_X86_64 && \
			sizeof(void *) == 8) || (swap_64(fatarch[i].cputype) == \
			CPU_TYPE_I386 && sizeof(void *) == 4))
			{
				ft_nm(obj + swap_64(fatarch[i].offset), end);
				break ;
			}
		}
		else
			print_err("Error corrupted\n", "");
	}
}

void			fat32_loop(void *obj, uint32_t nf, struct fat_arch *fatarch, \
																void *end)
{
	uint32_t		i;

	i = -1;
	while (++i < nf)
	{
		if (i == 0 && nf > 1)
			continue ;
		else if (obj + swap_32(fatarch[i].offset) < end)
		{
			if ((swap_32(fatarch[i].cputype) == CPU_TYPE_X86_64 && \
			sizeof(void *) == 8) || (swap_32(fatarch[i].cputype) == \
			CPU_TYPE_I386 && sizeof(void *) == 4))
			{
				ft_nm(obj + swap_32(fatarch[i].offset), end);
				break ;
			}
		}
		else
			print_err("Error corrupted\n", "");
	}
}

void			handle_fat(void *obj, void *end, int type)
{
	struct fat_header		*header;
	uint64_t				nf;
	struct fat_arch			*fatarch;
	int						i;

	header = (struct fat_header *)obj;
	if (type == 64)
		nf = swap_64(header->nfat_arch);
	else
		nf = swap_32(header->nfat_arch);
	fatarch = (struct fat_arch *)(header + 1);
	i = -1;
	if (type == 64)
		fat64_loop(obj, nf, fatarch, end);
	else
		fat32_loop(obj, nf, fatarch, end);
}
