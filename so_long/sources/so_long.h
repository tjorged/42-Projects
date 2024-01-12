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


typedef enum e_type {
	AD = 111,
	AD1 = 112,	
	AD2 = 113,
	AU = 114,
	AU1 = 115,
	AU2 = 116,
	AL = 117,
	AL1 = 118,
	AL2 = 119,
	AR = 120,
	AR1 = 121,
	AR2 = 122,
	UP = 119,
	LEFT = 97,
	DOWN = 115,
	RIGHT = 100
} t_type;

# define SCALER 1
# define SIZE (128/SCALER)

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
	int			player_x;
	int			player_y;
	int			player_state;
	int			movement_count;
	t_image		front;
	t_image		frame;
}	t_frame;

typedef struct s_map
{
	char	**map;
	char	**collisions;
	int		collect;
	int		height;
	int		width;
	int		player_y;
	int		player_x;
	int		exit_y;
	int		exit_x;
}	t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_frame 	*frame;
	t_map		*map;
	t_image		*asset;
	int			loop;
}	t_mlx;



//error_handler.c
void	delete_map(char **map, char mode);

//mapper_utils.c
void	coord_finder(t_map *map);

//map_checker.c
void	map_checker(t_map *map);

//mapper.c
void	**mapper(char *file, t_map *map);

//map_transformer_utils.c
void	transform(t_map *map, int y, int x);
int		ground(char current);

//map_transformer.c
void	inner_corners(t_map *map, int y, int x);
void	inner_corners2(t_map *map, int y, int x);
void	corners(t_map *map, int y, int x);
void	borders(t_map *map, int y, int x);

//assets_initializer.c
t_image 		*assets_initializer(t_mlx *mlx);

//layers_creator.c
void	ayers_creator(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset);
void	image_into_img(t_image *asset, t_image *image, int x1, int y1);

//frame_painter.c
void			refresh_back_frame(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset);
unsigned int	get_color(t_image *img, int x, int y);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void 			render(t_mlx *mlx, t_frame *frame);

//hooks.c
int		key_press(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);

//main.c
//loop.c
int		game_loop(t_mlx *mlx);

#endif
