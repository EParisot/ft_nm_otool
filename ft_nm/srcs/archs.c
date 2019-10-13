/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:59:32 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/13 12:59:32 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void						print_sym(t_symbol *sym)
{
	int						len;

	len = 8;
	if (sym->value)
	{
		while (--len)
			ft_putchar('0');
		ft_putnbr_hex_p(sym->value);
	}
	else
		ft_putstr("                ");
	ft_putchar(' ');
	ft_putstr((sym->type) ? "T ": "U ");
	ft_putstr(sym->name);
	ft_putchar('\n');
}

int							build_sym_list(struct nlist_64 *symtab, \
							char *str_table, int i, t_list **sym_list)
{
	t_symbol				*sym;
	t_list					*cur_sym;

	if ((sym = (t_symbol *)malloc(sizeof(t_symbol))) == NULL)
		return (-1);
	sym->name = (char *)str_table + symtab[i].n_un.n_strx;
	sym->type = symtab[i].n_type > N_EXT;
	sym->value = symtab[i].n_value;
	if (*sym_list == NULL)
	{
		if ((*sym_list = ft_lstnew(sym, sizeof(t_symbol))) == NULL)
			return (-1);
	}
	else
	{
		if ((cur_sym = ft_lstnew(sym, sizeof(t_symbol))) == NULL)
			return (-1);
		ft_lstaddend(sym_list, cur_sym);
	}
	//TODO sort list by names
	print_sym(sym);
	free(sym);
	return (0);
}

void						read_sym_table(char *obj, struct load_command *lc, \
											t_list **sym_list)
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
		if (build_sym_list(symtab, str_tab, i, sym_list) < 0)
		{
			print_err("Error malloc", "");
			return ;
		}
		++i;
	}
}

void						del(void *addr, size_t size)
{
	size = 0;
	free(addr);
}

void						handle_64(char *obj)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						nb_ld;
	int						i;
	t_list					*sym_list;

	sym_list = NULL;
	header = (struct mach_header_64*)obj;
	nb_ld = header->ncmds;
	i = 0;
	lc = (void *)obj + sizeof(struct mach_header_64);
	while (i++ < nb_ld)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			read_sym_table(obj, lc, &sym_list);
			ft_lstdel(&sym_list, del);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
