/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:28:07 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/26 14:28:09 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	to_img(t_image *asset, t_image *image, int x1, int y1)
{
	int		x;
	int		y;

	y = -1;
	while (++y < (128 / SCALER))
	{
		x = -1;
		while (++x < (128 / SCALER))
		{
			my_mlx_pixel_put(image, x + x1, y + y1, \
				get_color(asset, x * SCALER, y * SCALER));
		}
	}
}

static void	create_back(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int		y;
	int		x;

	frame->back.img = mlx_new_image(mlx->mlx, map->width * \
		mlx->s, map->height * mlx->s);
	frame->back.addr = mlx_get_data_addr(frame->back.img, &frame->back.bpp, \
		&frame->back.line_length, &frame->back.endian);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != '1' && asset[(int)map->map[y][x]].addr)
				to_img(&asset[(int)map->map[y][x]], &frame->back, \
				x * mlx->s, y * mlx->s);
			x++;
		}
		y++;
	}
}

static void	create_front(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int		y;
	int		x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == 5 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[54], &frame->front, x * mlx->s, (y - 1) * mlx->s);
			else if (map->map[y][x] == 77 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[74], &frame->front, x * mlx->s, (y - 1) * mlx->s);
			else if (map->map[y][x] == 99 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[94], &frame->front, x * mlx->s, (y - 1) * mlx->s);
			else if (map->map[y][x] == 3 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[34], &frame->front, x * mlx->s, (y - 1) * mlx->s);
			else if (map->map[y][x] == 1 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[41], &frame->front, x * mlx->s, (y - 1) * mlx->s);
			else if (map->map[y][x] == 2 && asset[(int)map->map[y][x]].addr)
				to_img(&asset[24], &frame->front, x * mlx->s, (y - 1) * mlx->s);
		}
	}
}

void	layers_creator(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	create_back(frame, map, mlx, asset);
	frame->front.img = mlx_new_image(mlx->mlx, map->width * (mlx->s), \
		map->height * mlx->s);
	frame->front.addr = mlx_get_data_addr(frame->front.img, \
		&frame->front.bpp, &frame->front.line_length, &frame->front.endian);
	create_front(frame, map, mlx, asset);
	frame->frame.img = mlx_new_image(mlx->mlx, map->width * mlx->s, \
		map->height * mlx->s);
	frame->frame.addr = mlx_get_data_addr(frame->frame.img, &frame->frame.bpp, \
		&frame->frame.line_length, &frame->frame.endian);
}
