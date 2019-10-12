/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:59:32 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/12 18:57:03 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void						print_sym(struct nlist_64 *symtab, \
										char *str_table, int i)
{
	int						len;

	len = 16 - 8;//TODO find a better way
	if (symtab[i].n_value)
	{
		while (--len)
			ft_putchar('0');
		ft_putnbr_hex_p(symtab[i].n_value);
	}
	else
		ft_putstr("                ");
	ft_putchar(' ');
	ft_putstr((symtab[i].n_type > N_EXT) ? "T ": "U ");
	ft_putstr((void*)(str_table + symtab[i].n_un.n_strx));
	ft_putchar('\n');
}

void						read_sym_table(char *obj, struct load_command *lc)
{
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*symtab;
	char					*str_tab;
	uint32_t				nb_sym;
	uint32_t				i;

	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + symtab_cmd->stroff;
	symtab = (void *)obj + symtab_cmd->symoff;
	nb_sym = symtab_cmd->nsyms;
	i = 0;
	while (i < nb_sym)
	{
		print_sym(symtab, str_tab, i);
		++i;
	}
}

void						handle_64(char *obj)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						nb_ld;
	int						i;

	header = (struct mach_header_64*)obj;
	nb_ld = header->ncmds;
	i = 0;
	lc = (void *)obj + sizeof(struct mach_header_64);
	while (i++ < nb_ld)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			read_sym_table(obj, lc);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
