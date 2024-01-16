/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:33:15 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/19 16:10:19 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_map(char **map, char mode)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	if (mode == 'e')
	{
		write(2, "INVALID MAP SNAKE!\n", 19);
		exit(0);
	}
}

void	destroy_assets(t_mlx *mlx, t_image *asset)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		if (asset[i].path)
			mlx_destroy_image(mlx->mlx, asset[i].img);
	}
}

void	end_game(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->mlx);
	destroy_assets(mlx, mlx->asset);
	mlx_destroy_image(mlx->mlx, mlx->frame->back.img);
	mlx_destroy_image(mlx->mlx, mlx->frame->front.img);
	mlx_destroy_image(mlx->mlx, mlx->frame->frame.img);
	if (mlx->map->collect_str)
		free(mlx->map->collect_str);
	if (mlx->steps_str)
		free(mlx->steps_str);
	if (mlx->asset)
		free(mlx->asset);
	if (mlx->timer)
		free(mlx->timer);
	delete_map(mlx->map->map, 0);
	delete_map(mlx->map->collisions, 0);
	sleep (1);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
