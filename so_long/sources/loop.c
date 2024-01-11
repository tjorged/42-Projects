#include "so_long.h"

static void 	asset_switcher(t_mlx *mlx)
{
	if (mlx->frame->movement_count == 16)
	{
		if (mlx->frame->player_state == UP)
			mlx->frame->player = mlx->asset[AU2];
		else if (mlx->frame->player_state == LEFT)
			mlx->frame->player = mlx->asset[AL2];
		else if (mlx->frame->player_state == DOWN)
			mlx->frame->player = mlx->asset[AD2];
		else if (mlx->frame->player_state == RIGHT)
			mlx->frame->player = mlx->asset[AR2];
	}
	else if (mlx->frame->movement_count == 32)
	{
		if (mlx->frame->player_state == UP)
			mlx->frame->player = mlx->asset[AU1];
		else if (mlx->frame->player_state == LEFT)
			mlx->frame->player = mlx->asset[AL1];
		else if (mlx->frame->player_state == DOWN)
			mlx->frame->player = mlx->asset[AD1];
		else if (mlx->frame->player_state == RIGHT)
			mlx->frame->player = mlx->asset[AR1];
		mlx->frame->movement_count = 0;
	}
}

static void		player_movement(t_mlx *mlx)
{
	if (mlx->frame->player_state == UP)
	{
		mlx->frame->player_y -= (3 * SCALER);
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == LEFT)
	{
		mlx->frame->player_x -= (3 * SCALER);
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == DOWN)
	{
		mlx->frame->player_y += (3 * SCALER);
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == RIGHT)
	{
		mlx->frame->player_x += (3 * SCALER);
		mlx->frame->movement_count++;
	}
	asset_switcher(mlx);
}

static void		collisions_check(t_mlx *mlx)
{
	if (mlx->map->collisions[(mlx->frame->player_y + (SIZE*3/8)) / SIZE]\
	[mlx->frame->player_x / SIZE] == '1' 
	&& mlx->frame->player_state == UP)
		mlx->frame->player_y += (3 * SCALER);
	if (mlx->map->collisions[(mlx->frame->player_y + (SIZE*3/8)) / SIZE]\
	[mlx->frame->player_x / SIZE] == '1' 
	&& mlx->frame->player_state == LEFT)
		mlx->frame->player_x += (3 * SCALER);
	if (mlx->map->collisions[(mlx->frame->player_y  + SIZE/2) / SIZE]\
	[mlx->frame->player_x / SIZE] == '1' 
	&& mlx->frame->player_state == DOWN)
		mlx->frame->player_y -= (3 * SCALER);
	if (mlx->map->collisions[(mlx->frame->player_y + (SIZE*3/8)) / SIZE]\
	[(mlx->frame->player_x + SIZE/4) / SIZE] == '1' 
	&& mlx->frame->player_state == RIGHT)
		mlx->frame->player_x -= (3 * SCALER);
}

int		game_loop(t_mlx *mlx)
{
	player_movement(mlx);
	collisions_check(mlx);
	render(mlx, mlx->frame);
	return (0);
}