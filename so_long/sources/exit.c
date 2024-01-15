#include "so_long.h"

static int	exit_check_up(t_mlx *mlx)
{
	if (mlx->map->map[(mlx->frame->player_y) / SIZE] \
    [(mlx->frame->player_x - SIZE / 7) / SIZE] == 88 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4 + SIZE / 7) / SIZE] == 88 \
    && mlx->map->map[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x + SIZE / 8) / SIZE] == 18)
	    return (1);
    else
        return (0);
}

static int  exit_check_left(t_mlx *mlx)
{
    if (mlx->map->map[(mlx->frame->player_y - SIZE / 8) / SIZE] \
	[(mlx->frame->player_x - 1) / SIZE] == 44 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x - 1) / SIZE] == 44 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x) / SIZE] == 14) \
	    return (1);
    else
        return (0);
}

static int  exit_check_right(t_mlx *mlx)
{
    if (mlx->map->map[(mlx->frame->player_y - SIZE / 8) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4 + 1) / SIZE] == 66 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4 + 1) / SIZE] == 66 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x) / SIZE] == 16) \
	    return (1);
    else
        return (0);
}

static int  exit_check_ground(t_mlx *mlx)
{
	if ((mlx->map->map[(mlx->frame->player_y) / SIZE] \
	[(mlx->frame->player_x + SIZE / 8) / SIZE] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x - SIZE / 7) / SIZE] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 2) / SIZE] \
	[(mlx->frame->player_x + SIZE / 8) / SIZE] == 101 \
	&& mlx->map->map[(mlx->frame->player_y + SIZE / 4) / SIZE] \
	[(mlx->frame->player_x + SIZE / 4 + SIZE / 7) / SIZE] == 101))
		return (1);
	else
		return (0);
}

void    exit_check(t_mlx *mlx)
{
	if (exit_check_up(mlx) || exit_check_left(mlx) \
	|| exit_check_right(mlx) || exit_check_ground(mlx))
		end_game(mlx);
}