# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:40:33 by eparisot          #+#    #+#              #
#    Updated: 2020/01/07 15:05:49 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm

SRCS	=	srcs/ft_nm.c \
			srcs/handle_64.c \
			srcs/handle_32.c \
			srcs/handle_fat.c \
			srcs/fat_tools.c \
			srcs/check_swaps.c \
			srcs/tools.c \
			srcs/tools2.c

INC		=	includes/ft_nm.h

OBJS	=	$(SRCS:.c=.o)
LIBS	=	../libft/libft.a \

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all		:	$(LIBS) $(NAME)

$(NAME)	:	$(OBJS) $(INC)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBS)	: 	.FORCE
	@$(MAKE) -C ../libft

.FORCE	:

clean	:
	$(RM) $(OBJS) && $(MAKE) clean -C ../libft

fclean	:	clean
	$(RM) $(NAME) ../libft/libft.a

re		:	fclean all

.PHONY	: all re clean fclean
