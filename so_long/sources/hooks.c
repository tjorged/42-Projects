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
		mlx->frame->player = mlx->asset[AU];
	if (keycode == LEFT && mlx->frame->player_state == LEFT)
		mlx->frame->player = mlx->asset[AL];
	if (keycode == DOWN && mlx->frame->player_state == DOWN)
		mlx->frame->player = mlx->asset[AD];
	if (keycode == RIGHT && mlx->frame->player_state == RIGHT)
		mlx->frame->player = mlx->asset[AR];
	if (keycode == 65307)
		mlx_do_key_autorepeaton(mlx->mlx);
	if (keycode == UP || keycode == LEFT || keycode == DOWN || keycode == RIGHT)
		mlx->frame->player_state = 0;
	ft_printf("You released the key:%i\n", keycode);
	return (0);
}