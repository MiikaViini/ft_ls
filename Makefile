# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/31 13:09:39 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_FILES = error.c flags.c flags2.c ft_ls.c init_and_mem.c long_format_info.c \
	open_and_save.c permissions.c print_long_format.c print_multicolumn.c \
	sort_args.c sort_args2.c sort_entrys.c utils.c utils2.c \

OBJ_DIR = objs

SRC_DIR = srcs

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = ./libft/libft.a


all: $(NAME)

$(NAME): $(OBJS) Makefile
	@make -C ./libft/
	@gcc $(FLAGS) $(SRCS) -o $(NAME) $(LIBFT) 
	@echo "\x1b[32;01mFt_ls compiled\x1b[32;01m"

$(OBJS): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c -I includes -o $@ $<

clean:
	@echo "\x1b[33;01mDeleting objs\x1b[33;01m"
	@make clean -C ./libft
	@/bin/rm -Rf $(OBJ_DIR)

fclean: clean
	@echo "\x1b[31;01mRemoving binary\x1b[31;01m"
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

