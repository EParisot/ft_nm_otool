/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:25:27 by eparisot          #+#    #+#             */
/*   Updated: 2020/01/07 13:29:21 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			del(void *addr, size_t size)
{
	size = 0;
	free(addr);
}

int				print_err(char *err, char *arg)
{
	ft_putstr(err);
	if (ft_strlen(arg))
	{
		ft_putstr(" '");
		ft_putstr(arg);
		ft_putstr("'");
	}
	ft_putchar('\n');
	return (1);
}

static void		ft_lstswap(t_list *lst, t_list *next)
{
	void		*mem;
	size_t		mem_size;

	mem = lst->content;
	mem_size = lst->content_size;
	lst->content = next->content;
	lst->content_size = next->content_size;
	next->content = mem;
	next->content_size = mem_size;
}

void			sym_lst_sort(t_list *sym_list)
{
	t_list		*first;
	int			i;
	int			lst_len;

	i = 0;
	lst_len = ft_lstcount(sym_list);
	first = sym_list;
	while (i++ < lst_len)
	{
		while (sym_list->next)
		{
			if (ft_strcmp(((t_symbol *)(sym_list->content))->name, \
					((t_symbol *)(sym_list->next->content))->name) > 0)
				ft_lstswap(sym_list, sym_list->next);
			else if (ft_strcmp(((t_symbol *)(sym_list->content))->name, \
					((t_symbol *)(sym_list->next->content))->name) == 0 && \
					((t_symbol *)(sym_list->content))->type > \
					((t_symbol *)(sym_list->next->content))->type)
				ft_lstswap(sym_list, sym_list->next);
			sym_list = sym_list->next;
		}
		sym_list = first;
	}
}

char			get_type(uint32_t num_type, uint8_t sect, t_sections *sects)
{
	char		res;

	if (sects == NULL)
		return (0);
	res = 'U';
	if ((num_type & N_TYPE) == N_ABS)
		res = 'A';
	else if ((num_type & N_TYPE) == N_INDR)
		res = 'I';
	else if ((num_type & N_TYPE) == N_SECT)
	{
		if (sect == sects->bss)
			res = 'B';
		else if (sect == sects->data)
			res = 'D';
		else if (sect == sects->text)
			res = 'T';
		else
			res = 'S';
	}
	if ((num_type & N_EXT) == 0)
		res = ft_tolower(res);
	return (res);
}
