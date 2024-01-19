/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_painter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:48:50 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	get_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render(t_mlx *mlx, t_frame *frame)
{
	int		y;
	int		x;

	y = -1;
	while (++y < mlx->map->height * mlx->s)
	{
		x = -1;
		while (++x < mlx->map->width * mlx->s)
		{
			my_mlx_pixel_put(&frame->frame, x, y, \
			get_color(&frame->back, x, y));
			if (x >= frame->player_x && x < frame->player_x + (mlx->s / 4) \
			&& y >= frame->player_y && y < frame->player_y + (mlx->s / 2))
			{
				my_mlx_pixel_put(&frame->frame, x, y, get_color(&frame->player, \
				(x - frame->player_x) * SCALER, \
				(y - frame->player_y) * SCALER));
			}
			my_mlx_pixel_put(&frame->frame, x, y, \
			get_color(&frame->front, x, y));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, frame->frame.img, 0, 0);
}

void	refresh_back(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int		y;
	int		x;

	if (mlx->map->collect == 0)
	{
		if (mlx->map->map[mlx->map->exit_y - 1][mlx->map->exit_x] == 88)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 18;
		else if (mlx->map->map[mlx->map->exit_y][mlx->map->exit_x - 1] == 44)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 14;
		else if (mlx->map->map[mlx->map->exit_y][mlx->map->exit_x + 1] == 66)
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 16;
		else
			mlx->map->map[mlx->map->exit_y][mlx->map->exit_x] = 101;
	}
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			if (map->map[y][x] != '1' && asset[(int)map->map[y][x]].addr)
				to_img(&asset[(int)map->map[y][x]], &frame->back, \
				x * mlx->s, y * mlx->s);
	}
}

void	print_coll_n_steps(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->window, mlx->s / 2, \
	mlx->map->height * mlx->s - mlx->s / 2, 0x00FFFFFF, \
		"REMAINING COLLECTIBLES:");
	mlx_string_put(mlx->mlx, mlx->window, mlx->s / 2 + 150, \
	mlx->map->height * mlx->s - mlx->s / 2, 0x00FFFFFF, mlx->map->collect_str);
	mlx_string_put(mlx->mlx, mlx->window, mlx->s / 2, \
	mlx->map->height * mlx->s - mlx->s / 2 + 20, 0x00FFFFFF, "STEPS:");
	mlx_string_put(mlx->mlx, mlx->window, mlx->s / 2 + 47, \
	mlx->map->height * mlx->s - mlx->s / 2 + 20, 0x00FFFFFF, mlx->steps_str);
}
