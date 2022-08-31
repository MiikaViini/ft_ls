# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:56:26 by mviinika          #+#    #+#              #
#    Updated: 2022/08/31 18:59:21 by mviinika         ###   ########.fr        #
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

FLAGS = -Wall -Werror -Wextra -O3

all: $(NAME) Makefile ft_printf.h

$(NAME): $(OBJS)
		@cp ../libft.a .
		@gcc $(FLAGS) -c $(SRCS)
		@ar rcs $(NAME) $(OBJS) ../libft.a
		@rm -f libft.a
		@echo "\x1b[32;01mFt_printf compiled\x1b[32;01m"


clean:
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re: fclean all
