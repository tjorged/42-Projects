#include "so_long.h"

char	coll_pivot(t_mlx *mlx, int offset_y, int offset_x)
{
	return (mlx->map->collisions[(mlx->frame->player_y + offset_y) / mlx->s][(mlx->frame->player_x + offset_x)/ mlx->s]);
}

int		y_walls(t_mlx *mlx)
{
	int		n;
	
	n = 0;
	while (mlx->frame->player_state_y == -1 && (coll_pivot(mlx, mlx->s * 3 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_y++;
		n++;
	}
	while (mlx->frame->player_state_y == 1 && (coll_pivot(mlx, mlx->s * 4 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 4 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_y--;
		n++;
	}
	return (n);
}

int		x_walls(t_mlx *mlx)
{
	int		n;
	
	n = 0;
	while (mlx->frame->player_state_x == -1 && (coll_pivot(mlx, mlx->s * 4 / 8, 0) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, 0) == '1'))
	{
		mlx->frame->player_x++;
		n++;
	}
	while (mlx->frame->player_state_x == 1 && (coll_pivot(mlx, mlx->s * 4 / 8, mlx->s * 2 / 8) == '1' \
	|| coll_pivot(mlx, mlx->s * 3 / 8, mlx->s * 2 / 8) == '1'))
	{
		mlx->frame->player_x--;
		n++;
	}
	return (n);
}

static void	asset_switcher(t_mlx *mlx, int mode)
{
	if (mode == 1) 
	{
		if (mlx->frame->player_state_y == -1)
			mlx->frame->player = mlx->asset[AU2];
		if (mlx->frame->player_state_y == 1)
			mlx->frame->player = mlx->asset[AD2];
		if (mlx->frame->player_state_x == -1)
			mlx->frame->player = mlx->asset[AL2];
		if (mlx->frame->player_state_x == 1)
			mlx->frame->player = mlx->asset[AR2];
	}
	else if (mode == 2) 
	{
		if (mlx->frame->player_state_y == -1)
			mlx->frame->player = mlx->asset[AU1];
		if (mlx->frame->player_state_y == 1)
			mlx->frame->player = mlx->asset[AD1];
		if (mlx->frame->player_state_x == -1)
			mlx->frame->player = mlx->asset[AL1];
		if (mlx->frame->player_state_x == 1)
			mlx->frame->player = mlx->asset[AR1];
		mlx->frame->movement_count = 0;
	}
	mlx->step_bol = 1;
}

static int		movement_maker(t_mlx *mlx, int x_wall, int y_wall)
{
	if (mlx->frame->player_state_x != 0 \
	&& mlx->frame->player_state_y != 0)
		mlx->mov = mlx->mov * 8 / 10;
	if (mlx->frame->player_state_y == -1)
		mlx->frame->player_y -= mlx->mov;
	if (mlx->frame->player_state_y == 1)
		mlx->frame->player_y += mlx->mov;
	y_wall = y_walls(mlx);
	if (mlx->frame->player_state_x == -1)
		mlx->frame->player_x -= mlx->mov;
	if (mlx->frame->player_state_x == 1)
		mlx->frame->player_x += mlx->mov;
	x_wall = x_walls(mlx);
	mlx->mov = ((650 / SCALER) / FRAME_RATE);
	mlx->frame->movement_count++;
	if (x_wall != 0 && y_wall != 0)
		return (x_wall + y_wall);
	if(x_wall != 0 && mlx->frame->player_state_y != 0)
		return (0);
	if(y_wall != 0 && mlx->frame->player_state_x != 0)
		return (0);
	return (x_wall + y_wall);
}

static void	player_movement(t_mlx *mlx)
{
	int	wall;

	wall = -1;
	if (mlx->frame->player_state_y != 0 || mlx->frame->player_state_x != 0)
		wall = movement_maker(mlx, 0, 0);
	if (mlx->frame->movement_count == (100 / (mlx->mov * 2)))
		asset_switcher(mlx, 1);
	else if (mlx->frame->movement_count == (100 / (mlx->mov * 2)) * 2)
		asset_switcher(mlx, 2);
	if (wall == 0 && mlx->step_bol == 1)
	{
		mlx->steps++;
		free(mlx->steps_str);
			mlx->steps_str = ft_itoa(mlx->steps); 
		mlx->step_bol = 0;
	}
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
