/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:41:26 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/12 13:22:55 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char			*get_obj_name(int argc, char **argv, char *obj_name)
{
	if (argc < 2 || ft_strlen(argv[1]) == 0)
	{
		if (!(obj_name = (char *)malloc(6 * sizeof(char))))
			return NULL;
		ft_strcpy(obj_name, "a.out\0");
	}
	else
	{
		if (!(obj_name = (char *)malloc(ft_strlen(argv[1]) * sizeof(char))))
			return NULL;
		ft_strcpy(obj_name, argv[1]);
	}
	return obj_name;
}

int				main(int argc, char *argv[])
{
	char		*obj_name;

	obj_name = NULL;
	obj_name = get_obj_name(argc, argv, obj_name);
	//TODO
	if (obj_name)
		ft_putendl(obj_name);
	free(obj_name);
	while (1);
	return 0;
}
