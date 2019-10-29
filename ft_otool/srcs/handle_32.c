/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:59:32 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/30 00:48:33 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

static void		print_32(void *obj, uint32_t i, uint32_t addr, uint32_t size)
{
	int				len;

	if (i % 16 == 0)
	{
		len = 8 - ft_countdigits_hex(addr + i);
		write(1, "00000000", len);
		ft_putnbr_hex_p((uintmax_t)(addr + i));
		ft_putchar('\t');
	}
	if (i < size)
	{
		len = ft_countdigits_hex((uintmax_t)(0xff & ((char *)obj)[i]));
		if (len < 2)
			ft_putchar('0');
		ft_putnbr_hex_p((uintmax_t)(0xff & ((char *)obj)[i]));
		ft_putchar(' ');
	}
	if (i % 16 == 15)
		ft_putchar('\n');
}

static int		print_txt_32(void *obj, uint64_t addr, uint32_t size, void *end)
{
	uint32_t					i;

	i = -1;
	if (obj + size > end)
		return (print_err("Error corrupted\n", ""));
	while (++i < size)
		print_32(obj, i, addr, size);
	ft_putchar('\n');
	return (0);
}

static void		parse_sects_32(void *obj, struct load_command *lc, \
									char *filename, void *end)
{
	struct segment_command		*segment_cmd;
	struct section				*sections;
	int							nb_sects;
	int							i;

	segment_cmd = (struct segment_command *)lc;
	sections = (struct section*)((void *)segment_cmd + sizeof(*segment_cmd));
	nb_sects = cpu_32(segment_cmd->nsects);
	i = -1;
	while (++i < nb_sects)
	{
		if (!ft_strcmp((sections + i)->sectname, SECT_TEXT) \
				&& !ft_strcmp((sections + i)->segname, SEG_TEXT))
		{
			ft_putstr(filename);
			ft_putstr(":\n");
			ft_putstr("Contents of (__TEXT,__text) section\n");
			print_txt_32(obj + cpu_32((sections + i)->offset), \
								cpu_32((sections + i)->addr), \
								cpu_32((sections + i)->size), end);
			break ;
		}
	}
}

void			handle_32(void *obj, void *end, char *filename)
{
	struct mach_header			*header;
	struct load_command			*lc;
	uint32_t					ncmds;

	header = (struct mach_header *)obj;
	lc = obj + sizeof(struct mach_header);
	ncmds = cpu_32(header->ncmds);
	while (ncmds-- && !check_corruption_32(obj, lc, end, filename))
	{
		if (cpu_32(lc->cmd) == LC_SEGMENT)
			parse_sects_32(obj, lc, filename, end);
		lc = (void *)lc + cpu_32(lc->cmdsize);
	}
}
