/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_initializer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:17:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/16 12:17:21 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	xpm_paths_2(t_image *asset)
{
	asset[AU].path = "./textures/entities/xpm/u.xpm";
	asset[AU1].path = "./textures/entities/xpm/u1.xpm";
	asset[AU2].path = "./textures/entities/xpm/u2.xpm";
	asset[AD].path = "./textures/entities/xpm/d.xpm";
	asset[AD1].path = "./textures/entities/xpm/d1.xpm";
	asset[AD2].path = "./textures/entities/xpm/d2.xpm";
	asset[AL].path = "./textures/entities/xpm/l.xpm";
	asset[AL1].path = "./textures/entities/xpm/l1.xpm";
	asset[AL2].path = "./textures/entities/xpm/l2.xpm";
	asset[AR].path = "./textures/entities/xpm/r.xpm";
	asset[AR1].path = "./textures/entities/xpm/r1.xpm";
	asset[AR2].path = "./textures/entities/xpm/r2.xpm";
	asset[24].path = "./textures/map/xpm/24.xpm";
	asset[34].path = "./textures/map/xpm/34.xpm";
	asset[41].path = "./textures/map/xpm/41.xpm";
	asset[94].path = "./textures/map/xpm/94.xpm";
	asset[74].path = "./textures/map/xpm/74.xpm";
}

static void	xpm_paths_1(t_image *asset)
{
	asset[1].path = "./textures/map/xpm/1.xpm";
	asset[2].path = "./textures/map/xpm/2.xpm";
	asset[3].path = "./textures/map/xpm/3.xpm";
	asset[4].path = "./textures/map/xpm/4.xpm";
	asset[5].path = "./textures/map/xpm/52.xpm";
	asset[6].path = "./textures/map/xpm/6.xpm";
	asset[7].path = "./textures/map/xpm/7.xpm";
	asset[8].path = "./textures/map/xpm/8.xpm";
	asset[9].path = "./textures/map/xpm/9.xpm";
	asset[14].path = "./textures/map/xpm/14.xpm";
	asset[18].path = "./textures/map/xpm/18.xpm";
	asset[16].path = "./textures/map/xpm/16.xpm";
	asset[11].path = "./textures/map/xpm/11.xpm";
	asset[33].path = "./textures/map/xpm/33.xpm";
	asset[44].path = "./textures/map/xpm/44.xpm";
	asset[66].path = "./textures/map/xpm/66.xpm";
	asset[77].path = "./textures/map/xpm/77.xpm";
	asset[88].path = "./textures/map/xpm/88.xpm";
	asset[99].path = "./textures/map/xpm/99.xpm"; 
	asset[69].path = "./textures/map/xpm/69.xpm";
	asset[101].path = "./textures/map/xpm/101.xpm";
	asset[67].path = "./textures/map/xpm/67.xpm";
	asset[48].path = "./textures/map/xpm/0.xpm";
	asset[54].path = "./textures/map/xpm/54.xpm";
}

static void	img_sizes(t_image *asset)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		if (i < 111)
		{
			asset[i].height = (128 / SCALER);
			asset[i].width = (128 / SCALER);
		}
		else
		{
			asset[i].height = (128 / SCALER) / 2;
			asset[i].width = (128 / SCALER) / 4;
		}
	}
}

static void	imgs_initializer(t_map *map, t_image *asset, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		if (asset[i].path)
		{
			asset[i].img = mlx_xpm_file_to_image(mlx->mlx, \
				asset[i].path, &asset[i].width, &asset[i].height);
			if (!asset[i].img)
			{
				destroy_assets(mlx, asset);
				free(mlx->mlx);
				delete_map(map->map, 'a');
				delete_map(map->collisions, 'c');
			}
			asset[i].addr = mlx_get_data_addr(asset[i].img, \
			&asset[i].bpp, &asset[i].line_length, &asset[i].endian);
		}
	}
}

t_image	*assets_initializer(t_mlx *mlx, t_map *map)
{
	int			i;
	t_image		*asset;

	mlx->s = (128 / SCALER);
	asset = malloc(sizeof(t_image) * 128);
	if (!asset)
	{
		free(mlx->mlx);
		delete_map(map->map, 'a');
		delete_map(map->collisions, 'c');
	}
	i = -1;
	while (++i < 128)
		asset[i].path = NULL;
	xpm_paths_1(asset);
	xpm_paths_2(asset);
	img_sizes(asset);
	imgs_initializer(map, asset, mlx);
	return (asset);
}
