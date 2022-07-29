# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 09:25:07 by mviinika          #+#    #+#              #
#    Updated: 2022/07/09 20:43:32 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putchar.c \
	ft_putendl_fd.c ft_putendl.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr_fd.c \
	ft_putstr.c ft_strcat.c ft_strchr.c ft_strclr.c \
	ft_strcmp.c ft_strcpy.c \
	ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
	ft_striteri.c ft_strjoin.c \
	ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	ft_strncmp.c ft_strncpy.c \
	ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
	ft_strsplit.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
	ft_strlcat.c \
	ft_lstadd.c ft_lstnew.c ft_lstiter.c ft_lstmap.c \
	ft_lstdelone.c ft_lstdel.c ft_strrev.c ft_lstrev.c \
	ft_lstaddlast.c ft_isspace.c ft_swap.c ft_strndup.c \
	ft_pow.c ft_dectobin.c ft_bintodec.c ft_abs.c ft_intlen.c \
	ft_itoabase.c ft_ftoa.c ft_ltoa.c ft_utoa.c ft_putstrlen.c \

OBJ = $(SRCS:.c=.o)

FT_PRINTF = ft_printf/libftprintf.a

GET_NEXT_LINE_SRC = get_next_line/get_next_line.c

GET_NEXT_LINE_OBJ = get_next_line.o

#INC = libft.h ft_printf/ft_printf.h  get_next_line/get_next_line.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):

	@gcc -c $(FLAGS) $(SRCS)
	@ar rcs $(NAME) $(OBJ)
	make -C ./ft_printf/
	cp $(FT_PRINTF) $(NAME)
	@gcc -c $(FLAGS) $(SRCS) $(GET_NEXT_LINE_SRC)
	@ar rcs $(NAME) $(OBJ) *.o $(GET_NEXT_LINE_OBJ)
clean:
	@rm -f $(OBJ) get_next_line.o

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME:.a=.so)
	@make fclean -C ./ft_printf

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJ)