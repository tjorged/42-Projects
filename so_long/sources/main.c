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
	t_map			map;
	t_frame			frame;
	t_image			*asset;
	int			j;
	int			i;

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


	printf("lenght = %i\n", map.lenght);
	printf("height = %i\n", map.height);
	printf("image = %li\n", sizeof(t_image));
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	asset = assets_initializer(&mlx);
	if (!asset)
		return (free(mlx.mlx), delete_map(map.map, 'a'), delete_map(map.collisions, 'e'), 1);
	mlx.window = mlx_new_window(mlx.mlx, map.lenght, map.height, "so_long");
	if (!mlx.window)
		return (free(mlx.mlx), 1);


	write(1, "oi\n", 3);
	/*layer_creator(&frame, &map, &mlx, asset);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &keylog, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, frame.back.img, 0, 0);
	mlx_hook(mlx.window, DestroyNotify, StructureNotifyMask, &end_mlx, &mlx);
	mlx_loop(mlx.mlx);*/
	delete_map(map.map, 'a');
	delete_map(map.collisions, 'a');
	return (0);
}
