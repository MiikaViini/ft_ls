# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/18 19:44:06 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c permissions.c sort_args.c sort_args2.c sort_entrys.c print.c \
	open_and_save.c flags.c flags2.c utils.c utils2.c init_and_mem.c \
	info.c error.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): Makefile ./libft $(OBJS)
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

