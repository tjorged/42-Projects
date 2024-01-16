#include "so_long.h"

static void	asset_switcher(t_mlx *mlx, int mode)
{
	if (mode == 1) 
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
	else if (mode == 2) 
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
	mlx->steps++;
}

static void	player_movement(t_mlx *mlx)
{
	if (mlx->frame->player_state != 0)
	{
		if (mlx->frame->player_state == UP)
			mlx->frame->player_y -= mlx->mov;
		else if (mlx->frame->player_state == LEFT)
			mlx->frame->player_x -= mlx->mov;
		else if (mlx->frame->player_state == DOWN)
			mlx->frame->player_y += mlx->mov;
		else if (mlx->frame->player_state == RIGHT)
			mlx->frame->player_x += mlx->mov;
		mlx->frame->movement_count++;
		if (mlx->frame->movement_count == (100 / (mlx->mov * 2)))
		{
			asset_switcher(mlx, 1);
			free(mlx->steps_str);
			mlx->steps_str = ft_itoa(mlx->steps);
		}
		else if (mlx->frame->movement_count == (100 / (mlx->mov * 2)) * 2)
		{
			asset_switcher(mlx, 2);
			free(mlx->steps_str);
			mlx->steps_str = ft_itoa(mlx->steps);
		}
	}
}

static void	collisions_check(t_mlx *mlx)
{
	if (mlx->frame->player_state == UP && (mlx->map->collisions \
	[(mlx->frame->player_y + (mlx->s * 3 / 8)) / mlx->s] \
	[mlx->frame->player_x / mlx->s] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (mlx->s * 3 / 8)) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4) / mlx->s] == '1'))
		mlx->frame->player_y = mlx->y * mlx->s + mlx->s - (mlx->s * 3 / 8);
	else if (mlx->frame->player_state == LEFT && (mlx->map->collisions \
	[(mlx->frame->player_y + (mlx->s * 4 / 8)) / mlx->s] \
	[mlx->frame->player_x / mlx->s] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (mlx->s * 3 / 8)) / mlx->s] \
	[mlx->frame->player_x / mlx->s] == '1'))
		mlx->frame->player_x = mlx->x * mlx->s + mlx->s;
	else if (mlx->frame->player_state == DOWN && (mlx->map->collisions \
	[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[mlx->frame->player_x / mlx->s] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4) / mlx->s] == '1'))
		mlx->frame->player_y = mlx->y * mlx->s + (mlx->s / 2) - 1;
	else if (mlx->frame->player_state == RIGHT && (mlx->map->collisions \
	[(mlx->frame->player_y + (mlx->s / 2)) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4) / mlx->s] == '1' \
	|| mlx->map->collisions[(mlx->frame->player_y + (mlx->s * 3 / 8)) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4) / mlx->s] == '1'))
		mlx->frame->player_x = mlx->x * mlx->s + ((mlx->s / 4) * 3) - 1;
}

static void	collectibles_check(t_mlx *mlx)
{
	if ((mlx->map->map[(mlx->frame->player_y) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 8) / mlx->s] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x - mlx->s / 7) / mlx->s] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 2) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 8) / mlx->s] == 'C' \
	&& mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
	[(mlx->frame->player_x + mlx->s / 4 + mlx->s / 7) / mlx->s] == 'C'))
	{
		mlx->map->map[(mlx->frame->player_y + mlx->s / 4) / mlx->s] \
		[(mlx->frame->player_x + mlx->s / 8) / mlx->s] = '0';
		mlx->map->collect--;
		free(mlx->map->collect_str);
		mlx->map->collect_str = ft_itoa(mlx->map->collect);
		refresh_back(mlx->frame, mlx->map, mlx, mlx->asset);
	}
}

int	game_loop(t_mlx *mlx)
{
	gettimeofday((struct timeval *)mlx->timer, NULL);
	if ((mlx->timer->tv_sec * 1000000 + \
	mlx->timer->tv_usec) > mlx->frame_time)
	{
		player_movement(mlx);
		collisions_check(mlx);
		exit_check(mlx);
		if (mlx->map->collect != 0)
			collectibles_check(mlx);
		render(mlx, mlx->frame);
		print_coll_n_steps(mlx);
		gettimeofday((struct timeval *)mlx->timer, NULL);
		mlx->frame_time = mlx->timer->tv_sec * 1000000 \
		+ mlx->timer->tv_usec + (1000000 / FRAME_RATE);
	}
	return (0);
}
