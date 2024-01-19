/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:49:00 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:49:03 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	state_refresher(t_mlx *mlx, int state)
{
	if (state == UP)
	{
		mlx->frame->player_state_y--;
	}
	else if (state == LEFT)
	{
		mlx->frame->player_state_x--;
		if (mlx->frame->movement_count == (2000 / (SPEED))) 
			mlx->frame->player = mlx->asset[AL1];
		else
			mlx->frame->player = mlx->asset[AL2];
	}
	else if (state == DOWN)
	{
		mlx->frame->player_state_y++;
	}
	else if (state == RIGHT)
	{
		mlx->frame->player_state_x++;
		if (mlx->frame->movement_count <= (2000 / (SPEED)))
			mlx->frame->player = mlx->asset[AR1];
		else
			mlx->frame->player = mlx->asset[AR2];
	}
	mlx->step_bol = 1;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == UP)
		state_refresher(mlx, UP);
	else if (keycode == LEFT)
		state_refresher(mlx, LEFT);
	else if (keycode == DOWN)
		state_refresher(mlx, DOWN);
	else if (keycode == RIGHT)
		state_refresher(mlx, RIGHT);
	return (0);
}

static void	static_asset(int keycode, t_mlx *mlx)
{
	if (keycode == UP && !mlx->frame->player_state_y \
	&& !mlx->frame->player_state_x)
		mlx->frame->player = mlx->asset[AU];
	else if (keycode == LEFT && !mlx->frame->player_state_y \
	&& !mlx->frame->player_state_x)
		mlx->frame->player = mlx->asset[AL];
	else if (keycode == DOWN && !mlx->frame->player_state_y \
	&& !mlx->frame->player_state_x)
		mlx->frame->player = mlx->asset[AD];
	else if (keycode == RIGHT && !mlx->frame->player_state_y \
	&& !mlx->frame->player_state_x)
		mlx->frame->player = mlx->asset[AR];
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		end_game(mlx);
	else if (keycode == UP)
		mlx->frame->player_state_y++;
	else if (keycode == LEFT)
		mlx->frame->player_state_x++;
	else if (keycode == DOWN)
		mlx->frame->player_state_y--;
	else if (keycode == RIGHT)
		mlx->frame->player_state_x--;
	if (!mlx->frame->player_state_y \
	&& !mlx->frame->player_state_x)
		mlx->frame->movement_count = 0;
	static_asset(keycode, mlx);
	return (0);
}
