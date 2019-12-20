/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:41:26 by eparisot          #+#    #+#             */
/*   Updated: 2019/11/12 17:28:54 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

char				*get_arch_name(int type)
{
	if (type == CPU_TYPE_I386)
		return ("i386");
	else if (type == CPU_TYPE_X86_64)
		return ("x86_64");
	else if (type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	return ("???");
}

void				ft_otool(void *obj, void *end, char *obj_name)
{
	unsigned int	magic_nb;

	magic_nb = *(int *)obj;
	if (magic_nb == MH_MAGIC_64 || magic_nb == MH_CIGAM_64)
	{
		(magic_nb == MH_MAGIC_64) ? set_cpu(0) : set_cpu(1);
		handle_64(obj, end, obj_name);
	}
	else if (magic_nb == MH_MAGIC || magic_nb == MH_CIGAM)
	{
		(magic_nb == MH_MAGIC) ? set_cpu(0) : set_cpu(1);
		handle_32(obj, end, obj_name);
	}
	else if (magic_nb == FAT_MAGIC_64 || magic_nb == FAT_CIGAM_64)
		handle_fat(obj, end, 64, obj_name);
	else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
		handle_fat(obj, end, 32, obj_name);
	else if (magic_nb == AR_MAGIC || magic_nb == AR_CIGAM)
		handle_arch(obj, end, obj_name);
	else
		ft_putstr("Error corrupted or not implemented\n");
}

static void			read_obj(char *obj_name)
{
	int				fd;
	void			*obj;
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
		ft_otool(obj, obj + buf.st_size, obj_name);
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
