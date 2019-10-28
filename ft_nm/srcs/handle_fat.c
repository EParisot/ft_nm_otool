/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:23:17 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/28 19:28:41 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			print_arch(char *filename, char *arch)
{
	ft_putchar('\n');
	ft_putstr(filename);
	ft_putstr(" (for architecture ");
	ft_putstr(arch);
	ft_putstr("):\n");
}

static void		fat64_loop(void *obj, uint64_t nf, void *end, char *filename)
{
	uint64_t			i;
	struct fat_arch		*fatarch;
	struct fat_header	*header;

	header = (struct fat_header *)obj;
	fatarch = (struct fat_arch *)(header + 1);
	i = -1;
	while (++i < nf)
	{
		if (obj + swap_64(fatarch[i].offset) < end)
		{
			if (i == 0 && nf > 1 && is_arch(swap_32(fatarch[i + 1].cputype)))
				continue ;
			if (nf - 1 > i)
				print_arch(filename, get_arch_name(swap_64(fatarch[i].cputype)));
			ft_nm(obj + swap_64(fatarch[i].offset), end, filename);
		}
		else
			print_err("Error corrupted\n", filename);
	}
}

static void		fat32_loop(void *obj, uint32_t nf, void *end, char *filename)
{
	uint32_t			i;
	struct fat_arch		*fatarch;
	struct fat_header	*header;

	header = (struct fat_header *)obj;
	fatarch = (struct fat_arch *)(header + 1);
	i = -1;
	while (++i < nf)
	{
		if (obj + swap_32(fatarch[i].offset) < end)
		{
			if (i == 0 && nf > 1 && is_arch(swap_32(fatarch[i + 1].cputype)))
				continue ;
			if (nf - 1 > i)
				print_arch(filename, get_arch_name(swap_32(fatarch[i].cputype)));
			ft_nm(obj + swap_32(fatarch[i].offset), end, filename);
		}
		else
			print_err("Error corrupted\n", filename);
	}
}

void			handle_fat(void *obj, void *end, int type, char *filename)
{
	struct fat_header		*header;
	uint64_t				nf;

	header = (struct fat_header *)obj;
	if (type == 64)
		nf = swap_64(header->nfat_arch);
	else
		nf = swap_32(header->nfat_arch);
	if (type == 64)
		fat64_loop(obj, nf, end, filename);
	else
		fat32_loop(obj, nf, end, filename);
}

int				handle_arch(void *obj, void *end, char *filename)
{
	struct ar_hdr		*header;
	char				*str;
	size_t				len;

	obj += SARMAG;
	header = (struct ar_hdr *)obj;
	obj += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (obj)
	{
		header = (struct ar_hdr *)obj;
		if (ft_atoi(header->ar_size) <= 0)
			return (print_err("Error corrupted\n", filename));
		str = obj + sizeof(struct ar_hdr);
		if (obj + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) >= end)
			return (print_err("Error corrupted\n", filename));
		print_arch(filename, str);
		len = ft_strlen(str);
		while (!str[len++]);
		ft_nm(obj + sizeof(struct ar_hdr) + len - 1, end, filename);
		obj += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (0);
}
