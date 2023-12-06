NAME= so_long

CC= cc
CFLAGS= -Wall -Werror -Wextra

SRC= $(addprefix sources/, $(SOURCES))
SOURCES= main.c get_next_line.c get_next_line_utils.c

OBJ_DIR= objects
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:sources/%.c=%.o))

MLX_DIR= ./mlx
MLX= $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ) $(MLX) 
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(MLX)

$(OBJ_DIR)/%.o: sources/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	cd $(MLX_DIR) && make

clean:
	rm -rf $(OBJ_DIR)
	cd $(MLX_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(MLX_DIR) && rm -f libmlx_Linux.a
	
re: fclean all

.PHONY: all fclean clean re
