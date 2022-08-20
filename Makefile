# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/08/20 20:18:11 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ft_ls.c permissions.c sort_args.c sort_args2.c sort_entrys.c print.c \
	open_and_save.c flags.c flags2.c flags3.c utils.c utils2.c init_and_mem.c \
	line_info.c error.c print_colors.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): ft_ls.h Makefile ./libft/ $(OBJS)
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

