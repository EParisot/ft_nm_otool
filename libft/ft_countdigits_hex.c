/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:28:01 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/26 18:58:35 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countdigits_hex(uintmax_t n)
{
	int		count;

	count = 1;
	if (n != 0)
	{
		while (n > 15)
		{
			n /= 16;
			count++;
		}
	}
	return (count);
}
