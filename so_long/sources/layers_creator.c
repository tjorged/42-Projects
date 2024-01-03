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

static void		image_into_img(t_image *asset, t_image *image, int x1, int y1)
{
	int		x;
	int		y;

	y = -1;
	while (++y < SIZE)
	{
		x = -1;
		while (++x < SIZE)
		{
			my_mlx_pixel_put(image, x + x1,  y + y1, \
				get_color(asset,  x * SCALER, y * SCALER));
		}
	}
}

static void		create_back_frame(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int		y;
	int		x;

	frame->back.img = mlx_new_image(mlx->mlx, map->width * SIZE, map->height * SIZE);
	frame->back.addr = mlx_get_data_addr(frame->back.img, &frame->back.bpp, 
				&frame->back.line_length, &frame->back.endian);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != '1' && asset[map->map[y][x]].addr)
				image_into_img(&asset[map->map[y][x]], &frame->back, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
}

static void		create_front_frame(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int		y;
	int		x;

	frame->front.img = mlx_new_image(mlx->mlx, map->width * SIZE, map->height * SIZE);
	frame->front.addr = mlx_get_data_addr(frame->front.img, &frame->front.bpp, 
				&frame->front.line_length, &frame->front.endian);
	y = 0;
	printf("%i\n", get_color(&frame->front,  0, 0));
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 5 && asset[map->map[y][x]].addr && asset[54].addr)
			{	
				image_into_img(&asset[54], &frame->front, x * SIZE, (y - 1) * SIZE);
			}
			x++;
		}
		y++;
	}
}




void	layers_creator(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	create_back_frame(frame, map, mlx, asset);
	create_front_frame(frame, map, mlx, asset);
	frame->frame.img = mlx_new_image(mlx->mlx, map->width * SIZE, map->height * SIZE);
	frame->frame.addr = mlx_get_data_addr(frame->frame.img, &frame->frame.bpp, 
				&frame->frame.line_length, &frame->frame.endian);
}
