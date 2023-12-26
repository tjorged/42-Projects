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

typedef struct	s_image
{
	void	*img;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
int	*get_color(t_image *img, int x, int y);
int		ground(char current, int mode);

#endif
