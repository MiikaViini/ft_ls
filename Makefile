# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/17 19:05:16 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c permissions.c sort_args.c sort_entrys.c print.c \
	recursion.c flags.c utils.c init_and_mem.c info.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
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
