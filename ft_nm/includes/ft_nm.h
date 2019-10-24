/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:39:01 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/24 15:03:12 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM

# define FT_NM

#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

typedef struct	s_symbol
{
	char		*name;
	uint8_t		type;
	uint64_t	value;
}				t_symbol;

typedef struct	s_sections
{
	int			text;
	int			data;
	int			bss;
}				t_sections;

void			print_err(char *err, char *arg);
void			handle_64(char *obj, void *end);
int				check_corruption(struct nlist_64 *symtab, void *end, \
															int nb_sym);
void			sym_lst_sort(t_list *sym_list);
char			get_type(uint32_t num_type, uint8_t sect, t_sections *sects);
void			del(void *addr, size_t size);

#endif
