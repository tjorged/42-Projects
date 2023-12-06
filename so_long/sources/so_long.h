#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"

typedef struct mlx
{
	void *mlx;
	void *window;
} t_mlx;

typedef struct asset
{
	void	*img;
	void	*path;
	int	w;
	int	h;
} t_asset;

#endif
