/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:27 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/04 15:48:24 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	vars_init(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	mlx_do_key_autorepeatoff(mlx->mlx);
	mlx->mov = ((250 / SCALER) / FRAME_RATE);
	mlx->x = (frame->player_x / mlx->s);
	mlx->y = (frame->player_y / mlx->s);
	frame->player_x = map->player_x * mlx->s + mlx->s / 3;
	frame->player_y = map->player_y * mlx->s + mlx->s / 3;
	frame->player = asset[AD];
	frame->player_state = 0;
	frame->movement_count = 0;
	mlx->frame = frame;
	mlx->map = map;
	mlx->asset = asset;
	mlx->map->collect_str = ft_itoa(map->collect);
	if (!map->collect_str)
		end_game(mlx);
	mlx->steps = 0;
	mlx->steps_str = ft_itoa(mlx->steps);
	if (!mlx->steps_str)
		end_game(mlx);
	mlx->timer = malloc(sizeof(t_timeval));
	if (!mlx->steps_str)
		end_game(mlx);
	mlx->frame_time = 1;
}

int	main(int argc, char *argv[])
{
	t_mlx				mlx;
	static t_map		map;
	t_frame				frame;
	t_image				*asset;

	if (argc != 2)
		exit(0);
	mapper(argv[1], &map);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (delete_map(map.map, 'a'), delete_map(map.collisions, 'a'), 1);
	asset = assets_initializer(&mlx, &map);
	mlx.window = mlx_new_window(mlx.mlx, map.width * (128 / SCALER), \
	map.height * (128 / SCALER), "so_long");
	if (!mlx.window)
		return (delete_map(map.map, 'a'), delete_map(map.collisions, 'a'), \
		free(mlx.mlx), destroy_assets(&mlx, asset), 1);
	layers_creator(&frame, &map, &mlx, asset);
	vars_init(&frame, &map, &mlx, asset);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, &key_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
