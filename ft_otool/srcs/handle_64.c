/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:59:32 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/30 03:01:09 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

static void		print_64(void *obj, uint64_t i, uint64_t addr, uint64_t size)
{
	int				len;

	if (i % 16 == 0)
	{
		len = 16 - ft_countdigits_hex(addr + i);
		write(1, "0000000000000000", len);
		ft_putnbr_hex_p((uintmax_t)(addr + i));
		ft_putchar('\t');
	}
	if (i < size)
	{
		len = ft_countdigits_hex((uintmax_t)(0xff & ((char *)obj)[i]));
		if (len < 2)
			ft_putchar('0');
		ft_putnbr_hex_p((uintmax_t)(0xff & ((char *)obj)[i]));
		if (*get_cpu() == 0)
			ft_putchar(' ');
		else if (i % 4 == 3)
			ft_putchar(' ');
	}
	if (i % 16 == 15)
		ft_putchar('\n');
}

static int		print_txt_64(void *obj, uint64_t addr, uint64_t size, void *end)
{
	uint64_t					i;

	i = -1;
	if (obj + size > end)
		return (print_err("Error corrupted\n", ""));
	while (++i < size)
		print_64(obj, i, addr, size);
	ft_putchar('\n');
	return (0);
}

static void		parse_sects_64(void *obj, struct load_command *lc, \
									char *filename, void *end)
{
	struct segment_command_64	*segment_cmd;
	struct section_64			*sections;
	int							nb_sects;
	int							i;

	segment_cmd = (struct segment_command_64 *)lc;
	sections = (struct section_64*)((void *)segment_cmd + sizeof(*segment_cmd));
	nb_sects = cpu_64(segment_cmd->nsects);
	i = -1;
	while (++i < nb_sects)
	{
		if (!ft_strcmp((sections + i)->sectname, SECT_TEXT) \
				&& !ft_strcmp((sections + i)->segname, SEG_TEXT))
		{
			ft_putstr(filename);
			ft_putstr(":\n");
			ft_putstr("Contents of (__TEXT,__text) section\n");
			print_txt_64(obj + cpu_64((sections + i)->offset), \
								cpu_64((sections + i)->addr), \
								cpu_64((sections + i)->size), end);
			break ;
		}
	}
}

void			handle_64(void *obj, void *end, char *filename)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	uint32_t					ncmds;

	header = (struct mach_header_64 *)obj;
	lc = obj + sizeof(struct mach_header_64);
	ncmds = cpu_64(header->ncmds);
	while (ncmds-- && !check_corruption_64(obj, lc, end, filename))
	{
		if (cpu_64(lc->cmd) == LC_SEGMENT_64)
			parse_sects_64(obj, lc, filename, end);
		lc = (void *)lc + cpu_64(lc->cmdsize);
	}
}
