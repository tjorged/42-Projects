#include "so_long.h"

int		key_press(int keycode, t_mlx *mlx)
{
	if (keycode == UP)
	{
		mlx->frame->player = mlx->asset[AU1];
		mlx->frame->player_state = UP;
		mlx->frame->movement_count = 0;
	}
	else if (keycode == LEFT)
	{
		mlx->frame->player = mlx->asset[AL1];
		mlx->frame->player_state = LEFT;
		mlx->frame->movement_count = 0;
	}
	else if (keycode == DOWN)
	{
		mlx->frame->player = mlx->asset[AD1];
		mlx->frame->player_state = DOWN;
		mlx->frame->movement_count = 0;
	}
    else if (keycode == RIGHT)
	{
		mlx->frame->player = mlx->asset[AR1];
		mlx->frame->player_state = RIGHT;
		mlx->frame->movement_count = 0;
	}
	ft_printf("You pressed the key:%i\n", keycode);
	return (0);
}

int		key_release(int keycode, t_mlx *mlx)
{
	if (keycode == UP && mlx->frame->player_state == UP)
	{
		mlx->frame->player = mlx->asset[AU];
		mlx->frame->player_state = 0;
	}
	if (keycode == LEFT && mlx->frame->player_state == LEFT)
	{
		mlx->frame->player = mlx->asset[AL];
		mlx->frame->player_state = 0;
	}
	if (keycode == DOWN && mlx->frame->player_state == DOWN)
	{
		mlx->frame->player = mlx->asset[AD];
		mlx->frame->player_state = 0;
	}
	if (keycode == RIGHT && mlx->frame->player_state == RIGHT)
	{
		mlx->frame->player = mlx->asset[AR];
		mlx->frame->player_state = 0;
	}
	if (keycode == 65307)
		end_game(mlx);
	ft_printf("You released the key:%i\n", keycode);
	return (0);
}