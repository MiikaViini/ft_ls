# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/09/05 10:03:52 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_FILES = error.c flags.c flags2.c ft_ls.c init_and_mem.c long_format_info.c \
	open_and_save.c permissions.c print_long_format.c print_multicolumn.c \
	sort_args.c sort_args2.c sort_entrys.c utils.c utils2.c

OBJS = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft/

INC = ./include/

##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01
RESET = \x1b[32;00m

all: $(NAME)

$(NAME): Makefile $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc -c $(FLAGS) $(SRC_FILES) -I $(INC)
	@gcc $(OBJS) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)Ft_ls compiled$(RESET)"

clean:
	@echo "$(YELLOW)Deleting ft_ls objs$(RESET)"
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME) $(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

