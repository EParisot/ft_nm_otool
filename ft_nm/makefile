# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:40:33 by eparisot          #+#    #+#              #
#    Updated: 2019/10/14 10:57:27 by eparisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm

SRCS	=	srcs/ft_nm.c \
			srcs/arch_64.c \
			srcs/tools.c

INC		=	includes/ft_nm.h

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
