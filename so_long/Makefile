NAME= so_long

CC= cc
CFLAGS= -g

SRC= $(addprefix sources/, $(SOURCES))
SOURCES= assets_initializer.c layers_creator.c main.c mapper.c mapper_utils.c error_handler.c map_checker.c map_transformer.c map_transformer_utils.c frame_painter.c player.c

OBJ_DIR= objects
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:sources/%.c=%.o))

MLX_DIR= ./mlx
MLX= $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(MLX) $(LIBFT)

$(OBJ_DIR)/%.o: sources/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	
re: fclean all

r: 
	make re && clear && ./so_long maps/map.ber

.PHONY: all fclean clean re
