# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:40:33 by eparisot          #+#    #+#              #
#    Updated: 2019/10/30 03:09:44 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_otool

SRCS	=	srcs/ft_otool.c \
			srcs/handle_64.c \
			srcs/handle_32.c \
			srcs/handle_fat.c \
			srcs/check_swaps.c \
			srcs/tools.c \
			srcs/tools2.c \

INC		=	includes/ft_otool.h

OBJS	=	$(SRCS:.c=.o)
LIBS	=	../libft/libft.a \

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all		:	$(LIBS) $(NAME)

$(NAME)	:	$(OBJS) $(INC)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBS)	:
	@$(MAKE) -C ../libft

clean	:
	$(RM) $(OBJS) && $(MAKE) clean -C ../libft

fclean	:	clean
	$(RM) $(NAME) ../libft/libft.a

re		:	fclean all
