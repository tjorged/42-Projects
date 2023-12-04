# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 14:20:29 by tjorge-d          #+#    #+#              #
#    Updated: 2023/10/30 15:44:45 by tjorge-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Werror -Wextra

SOURCE=ft_checker.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putstr.c ft_printf.c ft_putunbr.c
OBJ=$(SOURCE:.c=.o)

NAME=libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $@ $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
