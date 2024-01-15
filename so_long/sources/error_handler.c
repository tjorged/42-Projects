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

void	end_game(t_mlx *mlx)
{
	int	i;

	mlx_do_key_autorepeaton(mlx->mlx);
	free(mlx->timer);
	i = -1;
	while (++i < 128)
	{
		if (mlx->asset[i].path)
			mlx_destroy_image(mlx->mlx, mlx->asset[i].img);
	}
	delete_map(mlx->map->map, 0);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	sleep (3);
	exit(0);
}
