# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/09/02 09:55:30 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_FILES = error.c flags.c flags2.c ft_ls.c init_and_mem.c long_format_info.c \
	open_and_save.c permissions.c print_long_format.c print_multicolumn.c \
	sort_args.c sort_args2.c sort_entrys.c utils.c utils2.c

OBJS = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) Makefile ./include/ft_ls.h
	@make -C ./libft/
	@gcc -c $(FLAGS) $(SRC_FILES) -I ./include/
	@gcc $(OBJS) -o $(NAME) $(LIBFT)
	@echo "\x1b[32;01mFt_ls compiled\x1b[32;01m"


clean:
	@echo "\x1b[33;01mDeleting ft_ls objs\x1b[33;01m"
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@echo "\x1b[31;01mRemoving ft_ls\x1b[31;01m"
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

