#include "so_long.h"

static void	state_refresher(t_mlx *mlx, int state)
{
	if (state == UP)
		mlx->frame->player_state_y--;
	else if (state == LEFT)
		mlx->frame->player_state_x--;
	else if (state == DOWN)
		mlx->frame->player_state_y++;
	else if (state == RIGHT)
		mlx->frame->player_state_x++;
	mlx->frame->movement_count = 0;
	mlx->step_bol = 1;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == UP)
	{
		state_refresher(mlx, UP);
		mlx->frame->player = mlx->asset[AU1];
	}
	else if (keycode == LEFT)
	{
		state_refresher(mlx, LEFT);
		mlx->frame->player = mlx->asset[AL1];
	}
	else if (keycode == DOWN)
	{
		state_refresher(mlx, DOWN);
		mlx->frame->player = mlx->asset[AD1];
	}
	else if (keycode == RIGHT)
	{
		state_refresher(mlx, RIGHT);
		mlx->frame->player = mlx->asset[AR1];
	}
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == UP)
	{
	//	mlx->frame->player = mlx->asset[AU];
		mlx->frame->player_state_y++;
	}
	if (keycode == LEFT)
	{
	//	mlx->frame->player = mlx->asset[AL];
		mlx->frame->player_state_x++;
	}
	if (keycode == DOWN)
	{
	//	mlx->frame->player = mlx->asset[AD];
		mlx->frame->player_state_y--;
	}
	if (keycode == RIGHT)
	{
	//	mlx->frame->player = mlx->asset[AR];
		mlx->frame->player_state_x--;
	}
	if (keycode == 65307)
		end_game(mlx);
	return (0);
}
