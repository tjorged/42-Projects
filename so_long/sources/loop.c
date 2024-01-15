#include "so_long.h"

static void	asset_switcher(t_mlx *mlx)
{
	if (mlx->frame->movement_count == SWITCH_SPEED) 
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
	else if (mlx->frame->movement_count == SWITCH_SPEED * 2) 
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

static void	player_movement(t_mlx *mlx)
{
	if (mlx->frame->player_state == UP)
	{
		mlx->frame->player_y -= SPEED;
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == LEFT)
	{
		mlx->frame->player_x -= SPEED;
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == DOWN)
	{
		mlx->frame->player_y += SPEED;
		mlx->frame->movement_count++;
	}
	else if (mlx->frame->player_state == RIGHT)
	{
		mlx->frame->player_x += SPEED;
		mlx->frame->movement_count++;
	}
	asset_switcher(mlx);
}

static void	collisions_check(t_mlx *mlx)
{
	if (mlx->frame->player_state == UP && (mlx->map->collisions \
	[(mlx->frame->player_y + (SIZE * 3 / 8)) / SIZE] \
	[mlx->frame->player_x / SIZE] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (SIZE * 3 / 8)) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4) / SIZE] == '1'))
		mlx->frame->player_y = PLAYER_Y * SIZE + SIZE - (SIZE * 3 / 8);
	else if (mlx->frame->player_state == LEFT && (mlx->map->collisions \
	[(mlx->frame->player_y + (SIZE * 4 / 8)) / SIZE] \
	[mlx->frame->player_x / SIZE] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (SIZE * 3 / 8)) / SIZE] \
	[mlx->frame->player_x / SIZE] == '1'))
		mlx->frame->player_x = PLAYER_X * SIZE + SIZE;
	else if (mlx->frame->player_state == DOWN && (mlx->map->collisions \
	[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[mlx->frame->player_x / SIZE] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4) / SIZE] == '1'))
		mlx->frame->player_y = PLAYER_Y * SIZE + (SIZE / 2) - 1;
	else if (mlx->frame->player_state == RIGHT && (mlx->map->collisions \
	[(mlx->frame->player_y + (SIZE / 2)) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4) / SIZE] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (SIZE * 3 / 8)) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4) / SIZE] == '1'))
		mlx->frame->player_x = PLAYER_X * SIZE + ((SIZE / 4) * 3) - 1;
}

static void	collectibles_check(t_mlx *mlx)
{
	if ((mlx->map->map[(mlx->frame->player_y) / SIZE] \
	[(mlx->frame->player_x + SIZE / 8) / SIZE] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x - SIZE / 7) / SIZE] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x + SIZE / 8) / SIZE] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4 + SIZE / 7) / SIZE] == 'C'))
	{
		mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
		[(mlx->frame->player_x + SIZE / 8) / SIZE] = '0';
		mlx->map->collect--;
		if (mlx->map->collect == 0 && mlx->map->map[mlx->map->exit_y - 1] \
		[mlx->map->exit_x] == 88)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 18;
		else if (mlx->map->collect == 0 && mlx->map->map[mlx->map->exit_y] \
		[mlx->map->exit_x - 1] == 44)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 14;
		else if (mlx->map->collect == 0 && mlx->map->map[mlx->map->exit_y] \
		[mlx->map->exit_x + 1] == 66)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 16;
		else if (mlx->map->collect == 0)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 101;
		refresh_back_frame(mlx->frame, mlx->map, mlx, mlx->asset);
	}
}

int	game_loop(t_mlx *mlx)
{
	gettimeofday((struct timeval*)mlx->timer, NULL);
	if (mlx->timer->tv_usec >= mlx->frame_time \
	&& mlx->timer->tv_usec <= mlx->frame_time + (1000000 / FRAME_RATE))
	{
		player_movement(mlx);
		collisions_check(mlx);
		exit_check(mlx);
		if (mlx->map->collect != 0)
			collectibles_check(mlx);
		render(mlx, mlx->frame);
		gettimeofday((struct timeval*)mlx->timer, NULL);
		mlx->frame_time = mlx->timer->tv_usec + (1000000 / FRAME_RATE);
		if (mlx->frame_time >= 1000000)
			mlx->frame_time -= 1000000;
	}
	return (0);
}
