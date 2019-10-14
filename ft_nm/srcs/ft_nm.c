/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:41:26 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/14 17:16:43 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void				ft_nm(char *obj)
{
	unsigned int	magic_nb;

	magic_nb = *(int *)obj;
	if (magic_nb == MH_MAGIC_64)
		handle_64(obj);
}

void				read_obj(char *obj_name)
{
	int				fd;
	char			*obj;
	struct stat		buf;

	if ((fd = open(obj_name, O_RDONLY)) < 0)
		print_err("Error openning file", obj_name);
	if (fstat(fd, &buf) < 0)
		print_err("Error stating file", obj_name);
	if ((obj = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
			MAP_FAILED)
		print_err("Error reading file", obj_name);
	ft_nm(obj);
	if (munmap(obj, buf.st_size) < 0)
		print_err("Error munmap", "");
}

int					main(int argc, char *argv[])
{
	int				i;

	i = 0;
	if (argc >= 2)
		while (++i < argc)
			read_obj(argv[i]);
	else
		read_obj("a.out\0");
	return 0;
}
