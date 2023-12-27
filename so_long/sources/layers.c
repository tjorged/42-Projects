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
/*void	img_map_destroyer(t_assets **asset)
{

}*/

int	get_color(t_image *img, int x, int y)
{
	int    pixel;
	
	pixel = *(unsigned int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
	return (pixel);
}

/*void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}*/

t_image	*get_asset(t_map *map, t_image *asset, int x, int y)
{
	asset[(map->map[y / 128][x / 128])].addr = 
	mlx_get_data_addr(asset[(map->map[y / 128][x / 128])].img, 
	&asset[(map->map[y / 128][x / 128])].bits_per_pixel, 
	&asset[(map->map[y / 128][x / 128])].line_length, 
	&asset[(map->map[y / 128][x / 128])].endian);
	return (&asset[(map->map[y / 128][x / 128])]);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	layer_creator(t_frame *frame, t_map *map, t_mlx *mlx, t_image *asset)
{
	int	y;
	int	x;
	
	y = -1;
	frame->back.img = mlx_new_image(mlx, map->lenght * 128, map->height * 128);
	frame->back.addr = mlx_get_data_addr(frame->back.img, &frame->back.bits_per_pixel, 
				&frame->back.line_length, &frame->back.endian);
	while (++y < map->height * 128)
	{
		x = -1;
		while (++x < map->lenght * 128)
			my_mlx_pixel_put(&(frame->back), x, y, 
			get_color(get_asset(map, asset, x, y), x, y));
	}
}
