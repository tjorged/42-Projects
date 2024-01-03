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

void render(t_mlx *mlx)
{
	int		y;
	int		x;

	y = 0;
	while (y < mlx->map->height * SIZE)
	{
		x = 0;
		while (x < mlx->map->width * SIZE)
		{
			my_mlx_pixel_put(&mlx->frame->frame, x, y, 
			get_color(&mlx->frame->back,  x, y));
			my_mlx_pixel_put(&mlx->frame->frame, x, y, 
			get_color(&mlx->frame->player,  x, y));
			my_mlx_pixel_put(&mlx->frame->frame, x, y, 
			get_color(&mlx->frame->front,  x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame->frame.img, 0, 0);
}

int	end_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
	return (0);
}

int	keylog(int key, t_mlx *mlx)
{
	(void)mlx;
	printf("Pressed key: %d\n", key);
	return (0);
}

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
	mlx.window = mlx_new_window(mlx.mlx, map.width * (128/SCALER), 
	map.height * (128/SCALER), "so_long");
	if (!mlx.window)
		return (free(mlx.mlx), 1);
	
	// exit(0);
	mlx.frame = &frame;
	mlx.map = &map;
	layers_creator(&frame, &map, &mlx, asset);

	// mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &keylog, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);

	// mlx_hook(mlx.window, DestroyNotify, StructureNotifyMask, &end_mlx, &mlx);
	mlx_loop(mlx.mlx);
	delete_map(map.map, 'a');
	delete_map(map.collisions, 'a');
	return (0);
}
