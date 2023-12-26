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

static void	xpm_map_paths(t_image **asset)
{
	write(1, "OI\n", 3);
	asset[1]->path = "./assets/map/1.xpm";
	write(1, "OI\n", 3);
	asset[2]->path = "./assets/map/2.xpm";
	asset[3]->path = "./assets/map/3.xpm";
	asset[4]->path = "./assets/map/4.xpm";
	//asset[5]->path = "./assets/map/5.xpm";
	write(1, "OI\n", 3);
	//asset[6]->path = "./assets/map/6.xpm";
	write(1, "OI\n", 3);
	asset[7]->path = "./assets/map/7.xpm";
	asset[8]->path = "./assets/map/8.xpm";
	asset[9]->path = "./assets/map/9.xpm";
	asset[14]->path = "./assets/map/14.xpm";
	asset[16]->path = "./assets/map/18.xpm";
	asset[18]->path = "./assets/map/16.xpm";
	asset[11]->path = "./assets/map/11.xpm";
	asset[33]->path = "./assets/map/33.xpm";
	asset[44]->path = "./assets/map/44.xpm";
	asset[66]->path = "./assets/map/66.xpm";
	asset[77]->path = "./assets/map/77.xpm";
	asset[88]->path = "./assets/map/88.xpm";
	asset[99]->path = "./assets/map/99.xpm";
	asset['E']->path = "./assets/map/E.xpm";
	asset['e']->path = "./assets/map/e.xpm";
	asset['C']->path = "./assets/map/C.xpm";
	asset['0']->path = "./assets/map/0.xpm";
}

static void	img_map_initializer(t_image **asset, t_mlx *mlx)
{
	write(1, "OI\n", 3);
	asset[1]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[2]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[3]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[4]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[5]->img = mlx_new_image(mlx->mlx, 128, 208);
	asset[6]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[7]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[8]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[9]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[14]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[16]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[18]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[11]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[33]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[44]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[55]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[66]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[77]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[88]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset[99]->img = mlx_new_image(mlx->mlx, 128, 128);
	asset['E']->img = mlx_new_image(mlx->mlx, 128, 128);
	asset['e']->img = mlx_new_image(mlx->mlx, 128, 128);
	asset['C']->img = mlx_new_image(mlx->mlx, 128, 128);
}

int	*get_color(t_image *img, int x, int y)
{
	char    *pixel;
	
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (&*(int *)pixel);
}

/*void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}*/

t_image	*get_asset(t_map *map, t_image **asset, int x, int y)
{
	asset[(map->map[y / 128][x / 128])]->addr = 
	mlx_get_data_addr(asset[(map->map[y / 128][x / 128])]->img, 
	&asset[(map->map[y / 128][x / 128])]->bits_per_pixel, 
	&asset[(map->map[y / 128][x / 128])]->line_length, 
	&asset[(map->map[y / 128][x / 128])]->endian);
	return (asset[(map->map[y / 128][x / 128])]);
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
	xpm_map_paths(&asset);
	img_map_initializer(&asset, mlx);
	write(1, "OI\n", 3);
	frame->back.img = mlx_new_image(mlx, map->lenght * 128, map->height * 128);
	frame->back.addr = mlx_get_data_addr(frame->back.img, &frame->back.bits_per_pixel, 
				&frame->back.line_length, &frame->back.endian);
	while (++y < map->height * 128)
	{
		x = -1;
		while (++x < map->lenght * 128)
			my_mlx_pixel_put(&(frame->back), x, y, 
			*get_color(get_asset(map, &asset, x, y), x, y));
	}
}
