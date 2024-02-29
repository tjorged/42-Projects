NAME= philo

CC= cc
CFLAGS= -Wall -Werror -Wextra #-pthread -g -fsanitize=thread

SRC= $(addprefix sources/, $(SOURCES))
SOURCES= main.c parser.c philo_actions.c philo_utils.c philosophers.c threads.c

OBJ_DIR= objects
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:sources/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: sources/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re