NAME=push_swap
CC=cc
CFLAGS=-Wall -Werror -Wextra -g
SOURCE= main.c utils.c cleaner.c push_swap.c moves.c binary_divider.c
OBJ=$(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
