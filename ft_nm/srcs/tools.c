/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:25:27 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/13 21:17:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

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
			sym_list = sym_list->next;
		}
		sym_list = first;
	}
}

char			get_type(uint32_t num_type)
{
	char res;
	char ext;
	char type;

	res = 0;
	ext = num_type & N_EXT;
	type = num_type & N_TYPE;
	if (type == N_UNDF)
		res = 'U';
	else if (ext == 0)
		res = 't';
	else
		res = 'T';
	return (res);
}
