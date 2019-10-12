/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:17:23 by eparisot          #+#    #+#             */
/*   Updated: 2019/10/12 15:39:11 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

void			print_err(char *err, char *arg)
{
	ft_putstr(err);
	if (ft_strlen(arg))
	{
		ft_putstr(" '");
		ft_putstr(arg);
		ft_putstr("'");
	}
	ft_putchar('\n');
}

void			ft_otool(char *obj)
{

}

void			read_obj(char *obj_name)
{
	int			fd;
	char		*obj;
	struct stat buf;

	if ((fd = open(obj_name, O_RDONLY)) < 0)
		print_err("Error openning file", obj_name);
	if (fstat(fd, &buf) < 0)
		print_err("Error stating file", obj_name);
	if ((obj = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
			MAP_FAILED)
		print_err("Error reading file", obj_name);
	ft_otool(obj);
	if (munmap(obj, buf.st_size) < 0)
		print_err("Error munmap", "");
}

int				main(int argc, char *argv[])
{
	int		i;

	i = 0;
	if (argc >= 2)
		while (++i < argc)
			read_obj(argv[i]);
	else
		print_err("Error no arg", "");
	while (1);
	return 0;
}
