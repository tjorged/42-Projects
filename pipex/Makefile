NAME= tubochis

CC= cc
CFLAGS= -g	

SRC= $(addprefix sources/, $(SOURCES))
SOURCES= main.c

OBJ_DIR= objects
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:sources/%.c=%.o))

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: sources/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all fclean clean re
