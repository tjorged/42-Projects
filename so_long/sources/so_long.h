#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

typedef struct mlx
{
	void	*mlx;
	void	*window;
} t_mlx;

typedef struct map
{
	char	**map;
	char	**collisions;
	int	collect;
	int	row_count;
	int	lenght;
	int	exit_y;
	int	exit_x;
	int	player_y;
	int	player_x;
} t_map;

typedef struct asset
{
	void	*img;
	void	*path;
	int	w;
	int	h;
} t_asset;

void	delete_map(char **map, char mode);
void	coord_finder(t_map *map);
void	**mapper(char *file, t_map *map);
void	map_checker(t_map *map);
void	singles_handler(char *current, int corners, int sides);
void	map_transformer(t_map *map);
int	flor(char current);

#endif
