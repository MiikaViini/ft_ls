# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/07/31 11:34:01 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c permissions.c sort.c print.c \
	recursion.c flags.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -O3

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):
	@make -C ./libft/
	@gcc -c $(FLAGS) $(SRCS)
	@gcc $(OBJ) -o $(NAME) $(LIBFT)
clean:
	@make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
#	@rm -r $(NAME).dSYM
	@make fclean -C ./libft

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJ)
