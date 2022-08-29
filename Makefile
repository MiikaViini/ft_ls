# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/29 10:52:58 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = error.c flags.c flags2.c ft_ls.c init_and_mem.c long_format_info.c \
	open_and_save.c permissions.c print_long_format.c print_multicolumn.c \
	sort_args.c sort_args2.c sort_entrys.c utils.c utils2.c \

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) ft_ls.h Makefile
	@make -C ./libft/
	@gcc -c $(FLAGS) $(SRCS)
	@gcc $(OBJS) -o $(NAME) $(LIBFT)
clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
#	@rm -r $(NAME).dSYM
	@make fclean -C ./libft

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

