/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:49:58 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:50:00 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	coll_pivot(t_mlx *mlx, int offset_y, int offset_x)
{
	return (mlx->map->collisions[(mlx->frame->player_y \
	+ offset_y) / mlx->s][(mlx->frame->player_x + offset_x) / mlx->s]);
}

int	y_walls(t_mlx *mlx)
{
	int		n;

	n = 0;
	while (mlx->frame->player_state_y == -1 && \
	(coll_pivot(mlx, mlx->s * 3 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_y++;
		n++;
	}
	while (mlx->frame->player_state_y == 1 && \
	(coll_pivot(mlx, mlx->s * 4 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 4 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_y--;
		n++;
	}
	return (n);
}

int	x_walls(t_mlx *mlx)
{
	int		n;

	n = 0;
	while (mlx->frame->player_state_x == -1 && \
	(coll_pivot(mlx, mlx->s * 4 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, 0) == '1'))
	{
		mlx->frame->player_x++;
		n++;
	}
	while (mlx->frame->player_state_x == 1 && \
	(coll_pivot(mlx, mlx->s * 4 / 8, mlx->s * 2 / 8) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_x--;
		n++;
	}
	return (n);
}
