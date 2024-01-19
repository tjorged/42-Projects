/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:18:00 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/16 12:18:04 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	exit_check_up(t_mlx *mlx)
{
	if (mlx->map->map[(mlx->frame->player_y) / mlx->s] \
	[(mlx->frame->player_x - mlx->s / 7) / mlx->s] == 88 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4 + mlx->s / 7) / mlx->s] == 88 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 8) / mlx->s] == 18)
		return (1);
	else
		return (0);
}

static int	exit_check_left(t_mlx *mlx)
{
	if (mlx->map->map[(mlx->frame->player_y - mlx->s / 8) / mlx->s] \
	[(mlx->frame->player_x - 1) / mlx->s] == 44 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x - 1) / mlx->s] == 44 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x) / mlx->s] == 14)
		return (1);
	else
		return (0);
}

static int	exit_check_right(t_mlx *mlx)
{
	if (mlx->map->map[(mlx->frame->player_y - mlx->s / 8) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4 + 1) / mlx->s] == 66 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4 + 1) / mlx->s] == 66 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x) / mlx->s] == 16)
		return (1);
	else
		return (0);
}

static int	exit_check_ground(t_mlx *mlx)
{
	if ((mlx->map->map[(mlx->frame->player_y) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 8) / mlx->s] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x - mlx->s / 7) / mlx->s] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 8) / mlx->s] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4 + mlx->s / 7) / mlx->s] == 101))
		return (1);
	else
		return (0);
}

void	exit_check(t_mlx *mlx)
{
	if (exit_check_up(mlx) || exit_check_left(mlx) \
	|| exit_check_right(mlx) || exit_check_ground(mlx))
		end_game(mlx);
}
