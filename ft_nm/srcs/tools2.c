/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:59:22 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/26 11:34:13 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			check_corruption_64(char *obj, struct load_command *lc, void *end)
{
	int						i;
	struct symtab_command	*symtab_cmd;
	struct nlist_64			*symtab;
	int						nb_sym;
	char					*str_tab;

	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + symtab_cmd->stroff;
	symtab = (void *)obj + symtab_cmd->symoff;
	nb_sym = symtab_cmd->nsyms;
	i = 0;
	while (i < nb_sym)
	{
		if ((void *)symtab + i * sizeof(symtab) >= end || \
			(void *)str_tab + symtab[i].n_un.n_strx >= end || \
			(void *)str_tab + symtab[i + 1].n_un.n_strx >= end)
		{
			print_err("Error corrupted", "");
			return (1);
		}
		++i;
	}
	return (0);
}

int			check_corruption_32(char *obj, struct load_command *lc, void *end)
{
	int							i;
	struct symtab_command		*symtab_cmd;
	struct nlist				*symtab;
	int							nb_sym;
	char						*str_tab;

	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + symtab_cmd->stroff;
	symtab = (void *)obj + symtab_cmd->symoff;
	nb_sym = symtab_cmd->nsyms;
	i = 0;
	while (i < nb_sym)
	{
		if ((void *)symtab + i * sizeof(symtab) >= end || \
			(void *)str_tab + symtab[i].n_un.n_strx >= end || \
			(void *)str_tab + symtab[i + 1].n_un.n_strx >= end)
		{
			print_err("Error corrupted", "");
			return (1);
		}
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
	n = ((n << 8) & 0xFF00FF00FF00FF00ULL) \
		| ((n >> 8) & 0x00FF00FF00FF00FFULL);
	n = ((n << 16) & 0xFFFF0000FFFF0000ULL) \
		| ((n >> 16) & 0x0000FFFF0000FFFFULL);
	return ((n << 32) | (n >> 32));
}
