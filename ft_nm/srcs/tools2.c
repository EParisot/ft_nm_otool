/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:59:22 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/18 18:07:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			check_corruption(struct nlist_64 *symtab, void *end, int nb_sym)
{
	int							i;

	i = 0;
	while (i < nb_sym)
	{
		if ((void *)symtab + i * sizeof(symtab) >= end)
		{
			print_err("Error corrupted", "");
			return (1);
		}
		++i;
	}
	return (0);
}
