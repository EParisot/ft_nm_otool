/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:59:22 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/30 19:02:38 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

int			check_corruption_64(void *obj, struct load_command *lc, void *end, \
								char *filename)
{
	int						i;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*symtab;
	int						nb_sym;
	char					*str_tab;

	if ((void *)lc + cpu_64(lc->cmdsize) > end)
		return (print_err("Error corrupted", filename));
	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + cpu_64(symtab_cmd->stroff);
	symtab = obj + cpu_64(symtab_cmd->symoff);
	nb_sym = cpu_64(symtab_cmd->nsyms);
	i = 0;
	if (cpu_64(lc->cmd) == LC_SYMTAB)
		while (i < nb_sym)
		{
			if ((void *)symtab + i * sizeof(symtab) >= end || \
				(void *)str_tab + cpu_64(symtab[i].n_un.n_strx) >= end)
				return (print_err("Error corrupted", filename));
			++i;
		}
	return (0);
}

int			check_corruption_32(void *obj, struct load_command *lc, void *end, \
									char *filename)
{
	int							i;
	struct symtab_command		*symtab_cmd;
	struct nlist				*symtab;
	int							nb_sym;
	char						*str_tab;

	if ((void *)lc + cpu_32(lc->cmdsize) > end)
		return (print_err("Error corrupted", filename));
	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + cpu_32(symtab_cmd->stroff);
	symtab = obj + cpu_32(symtab_cmd->symoff);
	nb_sym = cpu_32(symtab_cmd->nsyms);
	i = 0;
	if (cpu_32(lc->cmd) == LC_SYMTAB)
		while (i < nb_sym)
		{
			if ((void *)symtab + i * sizeof(symtab) >= end || \
				(void *)str_tab + cpu_32(symtab[i].n_un.n_strx) >= end)
				return (print_err("Error corrupted", filename));
			++i;
		}
	return (0);
}

uint32_t	swap_32(uint32_t n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0xFF00FF);
	return ((n << 16) | (n >> 16));
}

uint64_t	swap_64(uint64_t n)
{
	n = ((n << 8) & 0xFF00FF00FF00FF00) | ((n >> 8) & 0x00FF00FF00FF00FF);
	n = ((n << 16) & 0xFFFF0000FFFF0000) | ((n >> 16) & 0x0000FFFF0000FFFF);
	return ((n << 32) | (n >> 32));
}
