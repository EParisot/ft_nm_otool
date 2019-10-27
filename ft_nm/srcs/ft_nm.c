/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:41:26 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/27 20:14:08 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static void			ft_nm(char *obj, void *end)
{
	unsigned int	magic_nb;

	magic_nb = *(int *)obj;
	if (magic_nb == MH_MAGIC_64 || magic_nb == MH_CIGAM_64)
	{
		(magic_nb == MH_MAGIC_64) ? set_cpu(0): set_cpu(1);
		handle_64(obj, end);
	}
	else if (magic_nb == MH_MAGIC || magic_nb == MH_CIGAM)
	{
		(magic_nb == MH_MAGIC) ? set_cpu(0): set_cpu(1);
		handle_32(obj, end);
	}
	else
		ft_putstr("Error corrupted or not implemented\n");
}

static void			read_obj(char *obj_name)
{
	int				fd;
	char			*obj;
	struct stat		buf;

	if ((fd = open(obj_name, O_RDONLY)) < 0)
	{
		print_err("Error openning file", obj_name);
		return ;
	}
	if (fstat(fd, &buf) < 0)
	{
		print_err("Error stating file", obj_name);
		close(fd);
		return ;
	}
	if ((obj = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
			MAP_FAILED)
		print_err("Error mapping file", obj_name);
	else
	{
		close(fd);
		ft_nm(obj, obj + buf.st_size);
		if (munmap(obj, buf.st_size) < 0)
			print_err("Error munmap", "");
	}
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
	return (0);
}
