# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:56:26 by mviinika          #+#    #+#              #
#    Updated: 2022/07/31 11:33:43 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c length.c \
	flags.c treat_with_mods.c \
	treat_width.c width.c \
	wildcard.c init_struct.c \
	check_edges.c precision.c\
	treat_precision.c \
	d_specifier.c c_specifier.c \
	p_specifier.c x_specifier.c \
	f_specifier.c o_specifier.c \
	s_specifier.c u_specifier.c \
	b_specifier.c \
	per_specifier.c other_mods.c

OBJS = $(SRCS:.c=.o)

CC = clang

FLAGS = -Wall -Werror -Wextra -O3

#INCLUDES = "ft_printf.h"

all: $(NAME)

$(NAME):
#		@make -C ../
		cp ../libft.a .
		@$(CC) $(FLAGS) -c $(SRCS)
		@ar rcs $(NAME) $(OBJS) ../libft.a
clean:
#@make fclean -C ./libft
		@rm -f *.o

fclean: clean
#@make fclean -C ./libft
		@rm -f $(NAME)
debug:
	@gcc main.c libftprintf.a

re: fclean all
