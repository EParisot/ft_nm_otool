/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:40:59 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/12 18:28:34 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*ft_w(int n, char *p, int i, int sign)
{
	p[i] = '\0';
	while (i--)
	{
		p[i] = n % 10 + 48;
		n /= 10;
	}
	if (sign == -1)
		p[0] = '-';
	return (p);
}

char			*ft_itoa(int n)
{
	int		i;
	int		tmp;
	char	*p;
	int		sign;

	sign = 1;
	i = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		i++;
		sign = -1;
	}
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		i++;
	}
	if ((p = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	return (ft_w(n, p, i, sign));
}
