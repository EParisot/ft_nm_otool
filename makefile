# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eparisot <eparisot@42.student.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/27 12:09:42 by eparisot          #+#    #+#              #
#    Updated: 2019/12/27 12:19:54 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all		:
	$(MAKE) -C ft_nm && $(MAKE) -C ft_otool

clean	:
	$(MAKE) clean -C ft_nm && $(MAKE) clean -C ft_otool

fclean	:
	$(MAKE) fclean -C ft_nm && $(MAKE) fclean -C ft_otool

re		:
	$(MAKE) re -C ft_nm && $(MAKE) re -C ft_otool

.PHONY : all re clean fclean

