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
# include <sys/time.h>

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
}	t_type;

# define SCALER 2
# define SPEED 8
# define FRAME_RATE 30

typedef struct s_timeval
{
	time_t			tv_sec;
	suseconds_t		tv_usec;
}	t_timeval;

typedef struct s_image
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

typedef struct s_frame
{
	t_image		back;
	t_image		player;
	int			player_x;
	int			player_y;
	int			player_state_x;
	int			player_state_y;
	int			movement_count;
	int			current_asset;
	t_image		front;
	t_image		frame;
}	t_frame;

typedef struct s_map
{
	char	**map;
	char	**collisions;
	char	*collect_str;
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
	t_frame		*frame;
	t_map		*map;
	t_image		*asset;
	t_timeval	*timer;
	long		frame_time;
	int			steps;
	int			step_bol;
	char		*steps_str;
	int			s;
	int			mov;
	int			x;
	int			y;
}	t_mlx;

//so_long_utils.c
int				end_game(t_mlx *mlx);
void			coord_finder(t_map *map);
void			destroy_assets(t_mlx *mlx, t_image *asset);
void			delete_map(char **map, char mode);
void			vars_init(t_frame *frame, t_map *map, \
					t_mlx *mlx, t_image *asset);

//map_checker.c
void			map_checker(t_map *map);

//mapper.c
void			**mapper(char *file, t_map *map);

//map_transformer_utils.c
void			transform(t_map *map, int y, int x);
int				ground(char current);

//map_transformer.c
void			inner_corners(t_map *map, int y, int x);
void			inner_corners2(t_map *map, int y, int x);
void			corners(t_map *map, int y, int x);
void			borders(t_map *map, int y, int x);

//assets_initializer.c
t_image			*assets_initializer(t_mlx *mlx, t_map *map);

//layers_creator.c
void			layers_creator(t_frame *frame, t_map *map, \
					t_mlx *mlx, t_image *asset);
void			to_img(t_image *asset, t_image *image, int x1, int y1);

//frame_painter.c
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			render(t_mlx *mlx, t_frame *frame);
void			print_coll_n_steps(t_mlx *mlx);
void			refresh_back(t_frame *frame, t_map *map, \
					t_mlx *mlx, t_image *asset);
unsigned int	get_color(t_image *img, int x, int y);

//hooks.c
int				key_press(int keycode, t_mlx *mlx);
int				key_release(int keycode, t_mlx *mlx);

//borders.c
void			borders_refiner(t_map *map, int y, int x);

//loop.c
int				game_loop(t_mlx *mlx);

//exit_check.c
void			exit_check(t_mlx *mlx);

//loop_helper.c
char			coll_pivot(t_mlx *mlx, int offset_y, int offset_x);
int				y_walls(t_mlx *mlx);
int				x_walls(t_mlx *mlx);

#endif
