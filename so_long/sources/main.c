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

static int	incorret_args_nb(int argc)
{
	write(2, "Error\n", 6);
	if (argc < 2)
		return (ft_printf("You need to send a map Snake...\n"));
	else
		return (ft_printf("One map Snake... ONE!\n"));
}

int	main(int argc, char *argv[])
{
	t_mlx				mlx;
	static t_map		map;
	t_frame				frame;
	t_image				*asset;

	if (argc != 2)
		return (incorret_args_nb(argc));
	mapper(argv[1], &map);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (delete_map(map.map, '0'), delete_map(map.collisions, 'a'), 1);
	asset = assets_initializer(&mlx, &map);
	mlx.window = mlx_new_window(mlx.mlx, map.width * (128 / SCALER), \
	map.height * (128 / SCALER), "so_long");
	if (!mlx.window)
		return (delete_map(map.map, 'a'), delete_map(map.collisions, 'a'), \
		free(mlx.mlx), destroy_assets(&mlx, asset), 1);
	layers_creator(&frame, &map, &mlx, asset);
	vars_init(&frame, &map, &mlx, asset);
	mlx_hook(mlx.window, DestroyNotify, StructureNotifyMask, &end_game, &mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, &key_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
