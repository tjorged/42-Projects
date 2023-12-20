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
	int	collect;
} t_map;

typedef struct asset
{
	void	*img;
	void	*path;
	int	w;
	int	h;
} t_asset;

void	file_name_checker(char *file);
void	**mapper(char *file, t_map *info);
void	delete_map(char **map, char mode);
void	wall_checker(char **map, int y, int x, int max_y);
void	char_checker(char **map, int y, int x, t_map *info);

#endif
