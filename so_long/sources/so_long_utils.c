/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:50:21 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	coord_finder(t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
		{
			if (map->collisions[j][i] == 'E')
			{
				map->exit_y = j;
				map->exit_x = i;
			}
			if (map->collisions[j][i] == 'P')
			{
				map->player_y = j;
				map->player_x = i;
			}
		}
	}
}

void	vars_init(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	mlx_do_key_autorepeatoff(mlx->mlx);
	mlx->mov = ((SPEED / SCALER) / (FRAME_RATE / 30));
	frame->player_x = map->player_x * mlx->s + mlx->s / 3;
	frame->player_y = map->player_y * mlx->s + mlx->s / 3;
	frame->player_state_x = 0;
	frame->player_state_y = 0;
	frame->player = asset[AD];
	frame->movement_count = 0;
	mlx->step_bol = 0;
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

void	delete_map(char **map, char mode)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	if (mode == 'e' || mode == 'c')
	{
		write(2, "Error\n", 6);
		if (mode == 'e')
			ft_printf("Invalid map Snake!\n");
		exit(0);
	}
}

void	destroy_assets(t_mlx *mlx, t_image *asset)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		if (asset[i].path && asset[i].img)
			mlx_destroy_image(mlx->mlx, asset[i].img);
	}
}

int	end_game(t_mlx *mlx)
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
	return (0);
}
