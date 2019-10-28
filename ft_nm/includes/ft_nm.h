/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:39:01 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/28 13:46:15 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM

# define FT_NM

# include "../../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

typedef struct	s_symbol
{
	char		*name;
	uintmax_t	value;
	uint8_t		type;
}				t_symbol;

typedef struct	s_sections
{
	uint32_t	idx;
	int			text;
	int			data;
	int			bss;
}				t_sections;

void			ft_nm(void *obj, void *end);
void			handle_64(void *obj, void *end);
void			handle_32(void *obj, void *end);
void			handle_fat(void *obj, void *end, int type);
int				check_corruption_64(void *obj, struct load_command *lc, \
					void *end);
int				check_corruption_32(void *obj, struct load_command *lc, \
					void *end);
void			set_cpu(u_int8_t cpu);
uint32_t		cpu_32(uint32_t n);
uint64_t		cpu_64(uint64_t n);
uint32_t		swap_32(uint32_t n);
uint64_t		swap_64(uint64_t n);
int				print_err(char *err, char *arg);
size_t			secure_len(t_list *symlist, void *end);
void			sym_lst_sort(t_list *sym_list);
char			get_type(uint32_t num_type, uint8_t sect, t_sections *sects);
void			del(void *addr, size_t size);

#endif
