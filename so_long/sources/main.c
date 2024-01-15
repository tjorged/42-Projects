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

int	main(int argc, char *argv[])
{
	t_mlx			mlx;
	static t_map			map;
	t_frame			frame;
	t_image			*asset;
	int			j;
	int			i;

	if (argc != 2)
		exit(0);
	mapper(argv[1], &map);
	j = -1;
	while (map.map[++j])
	{
		i = -1;
		while (map.map[j][++i] != '\n')
		{
			if (map.map[j][i] < 10)
				printf("%i    ", map.map[j][i]);
			else if (map.map[j][i] < 100)
				printf("%i   ", map.map[j][i]);
			else
				printf("%i  ", map.map[j][i]);
		}
		printf("\n");
	}

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	asset = assets_initializer(&mlx);
	if (!asset)
		return (free(mlx.mlx), delete_map(map.map, 'a'), delete_map(map.collisions, 'e'), 1);
	mlx.window = mlx_new_window(mlx.mlx, map.width * SIZE, 
	map.height * SIZE, "so_long");
	if (!mlx.window)
		return (free(mlx.mlx), 1);

	frame.player_x = map.player_x * SIZE + SIZE / 3;
	frame.player_y = map.player_y * SIZE + SIZE / 3;
	frame.player = asset[AD];
	frame.player_state = 0;
	frame.movement_count = 0;
	mlx.frame = &frame;
	mlx.map = &map;
	mlx.asset = asset;
	mlx.timer = malloc(sizeof(t_timeval));
	mlx.frame_time = 1;
	layers_creator(&frame, &map, &mlx, asset);
	mlx_do_key_autorepeatoff(mlx.mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, &key_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}