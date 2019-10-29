/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:59:32 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/29 18:23:29 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static void			print_sym(t_list *sym_list, void *end)
{
	int							len;
	t_list						*first;

	first = sym_list;
	while (sym_list)
	{
		len = 9 - ft_countdigits_hex(((t_symbol *)(sym_list->content))->value);
		if (((t_symbol *)(sym_list->content))->type != 'U' && \
			((t_symbol *)(sym_list->content))->type != 'u')
		{
			while (--len)
				ft_putchar('0');
			ft_putnbr_hex_p((uintmax_t)((t_symbol*)(sym_list->content))->value);
		}
		else
			ft_putstr("        ");
		ft_putchar(' ');
		ft_putchar(((t_symbol *)(sym_list->content))->type);
		ft_putchar(' ');
		write(1, ((t_symbol *)(sym_list->content))->name, \
				secure_len(sym_list, end));
		ft_putchar('\n');
		sym_list = sym_list->next;
	}
	sym_list = first;
}

static int			build_sym_list(struct nlist symtab, \
						char *str_table, t_list **sym_list, t_sections *sects)
{
	t_symbol					*sym;
	t_list						*cur_sym;
	int							ret;

	ret = 0;
	if ((sym = (t_symbol *)malloc(sizeof(t_symbol))) == NULL)
		return (-1);
	sym->name = (char *)str_table + cpu_32(symtab.n_un.n_strx);
	sym->type = get_type(symtab.n_type, symtab.n_sect, sects);
	sym->value = cpu_32(symtab.n_value);
	if (*sym_list == NULL)
	{
		if ((*sym_list = ft_lstnew(sym, sizeof(t_symbol))) == NULL)
			ret = -1;
	}
	else
	{
		if ((cur_sym = ft_lstnew(sym, sizeof(t_symbol))) == NULL)
			ret = -1;
		else
			ft_lstaddend(sym_list, cur_sym);
	}
	free(sym);
	return (ret);
}

static void			read_sym_table(void *obj, struct load_command *lc, \
									t_list **sym_list, t_sections *sects)
{
	struct symtab_command		*symtab_cmd;
	struct nlist				*symtab;
	char						*str_tab;
	int							nb_sym;
	int							i;

	symtab_cmd = (struct symtab_command *)lc;
	str_tab = obj + cpu_32(symtab_cmd->stroff);
	symtab = obj + cpu_32(symtab_cmd->symoff);
	nb_sym = cpu_32(symtab_cmd->nsyms);
	i = 0;
	while (i < nb_sym)
	{
		if ((symtab[i].n_type & N_STAB) == 0 && \
			build_sym_list(symtab[i], str_tab, sym_list, sects) < 0)
		{
			print_err("Error malloc", "");
			return ;
		}
		++i;
	}
	sym_lst_sort(*sym_list);
}

static t_sections	*parse_sects(struct load_command *lc, \
									t_sections *sects)
{
	struct segment_command		*segment_cmd;
	struct section				*sections;
	int							nb_sects;
	int							i;

	if (sects == NULL && !(sects = (t_sections *)malloc(sizeof(t_sections))))
		return (NULL);
	if (sects == NULL)
		ft_bzero(sects, sizeof(t_sections));
	segment_cmd = (struct segment_command *)lc;
	sections = (struct section*)((void *)segment_cmd + sizeof(*segment_cmd));
	nb_sects = cpu_32(segment_cmd->nsects);
	i = -1;
	while (++i < nb_sects && ++sects->idx >= 0)
		if (!ft_strcmp((sections + i)->sectname, SECT_TEXT) \
				&& !ft_strcmp((sections + i)->segname, SEG_TEXT))
			sects->text = sects->idx;
		else if (!ft_strcmp((sections + i)->sectname, SECT_DATA) \
				&& !ft_strcmp((sections + i)->segname, SEG_DATA))
			sects->data = sects->idx;
		else if (!ft_strcmp((sections + i)->sectname, SECT_BSS) \
				&& !ft_strcmp((sections + i)->segname, SEG_DATA))
			sects->bss = sects->idx;
	return (sects);
}

void				handle_32(void *obj, void *end, char *filename)
{
	struct mach_header			*header;
	struct load_command			*lc;
	uint32_t					ncmds;
	t_list						*sym_list;
	t_sections					*sects;

	sym_list = NULL;
	sects = NULL;
	header = (struct mach_header *)obj;
	lc = obj + sizeof(struct mach_header);
	ncmds = cpu_32(header->ncmds);
	while (ncmds-- && !check_corruption_32(obj, lc, end, filename))
	{
		if (cpu_32(lc->cmd) == LC_SEGMENT)
			sects = parse_sects(lc, sects);
		if (cpu_32(lc->cmd) == LC_SYMTAB)
		{
			read_sym_table(obj, lc, &sym_list, sects);
			print_sym(sym_list, end);
			break ;
		}
		lc = (void *)lc + cpu_32(lc->cmdsize);
	}
	ft_lstdel(&sym_list, del);
	free(sects);
}
