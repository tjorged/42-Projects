/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:00:59 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/26 14:01:03 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define a1 0
# define a2 1
# define a3 2
# define a4 3
# define a5 4
# define a6 5
# define a7 6
# define a8 7
# define a9 8
# define a11 9
# define a33 10
# define a44 11
# define a66 12
# define a77 13
# define a88 14
# define a99 15
# define aE 16
# define ae 17
# define aC 18
# define a0 19
# define a14 20
# define a18 21
# define a16 22
# define ad 23
# define ad1 24
# define ad2 25
# define au 26
# define au1 27
# define au2 28
# define al 29
# define al1 30
# define al2 31
# define ar 32
# define ar1 33
# define ar2 34


typedef struct	s_image
{
	void	*img;
	char	*addr;
	char	*path;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_image;

typedef struct	s_frame
{
	t_image		back;
	t_image		player;
	t_image		front;
}	t_frame;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_map
{
	char	**map;
	char	**collisions;
	int		collect;
	int		height;
	int		lenght;
	int		exit_y;
	int		exit_x;
	int		player_y;
	int		player_x;
}	t_map;

void	delete_map(char **map, char mode);
void	coord_finder(t_map *map);
void	**mapper(char *file, t_map *map);
void	map_checker(t_map *map);
void	map_transformer(t_map *map);
void	inner_corners(t_map *map, int y, int x);
void	layer_creator(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int	get_color(t_image *img, int x, int y);
int		ground(char current, int mode);
t_image *assets_initializer(t_mlx *mlx);

#endif
