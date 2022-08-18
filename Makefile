# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/18 14:13:01 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c permissions.c sort_args.c sort_args2.c sort_entrys.c print.c \
	recursion.c flags.c flags2.c utils.c utils2.c init_and_mem.c \
	info.c error.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) Makefile libft
	@make -C ./libft/
	@gcc -c $(FLAGS) $(SRCS)
	@gcc $(OBJ) -o $(NAME) $(LIBFT)
clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
#	@rm -r $(NAME).dSYM
	@make fclean -C ./libft

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJ)

