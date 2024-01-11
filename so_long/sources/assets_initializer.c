#include "so_long.h"

static void xpm_entities_paths(t_image *asset)
{
    asset[AU].path = "./assets/entities/xpm/u.xpm";
	asset[AU1].path = "./assets/entities/xpm/u1.xpm";
	asset[AU2].path = "./assets/entities/xpm/u2.xpm";
	asset[AD].path = "./assets/entities/xpm/d.xpm";
	asset[AD1].path = "./assets/entities/xpm/d1.xpm";
	asset[AD2].path = "./assets/entities/xpm/d2.xpm";
	asset[AL].path = "./assets/entities/xpm/l.xpm";
	asset[AL1].path = "./assets/entities/xpm/l1.xpm";
	asset[AL2].path = "./assets/entities/xpm/l2.xpm";
	asset[AR].path = "./assets/entities/xpm/r.xpm";
	asset[AR1].path = "./assets/entities/xpm/r1.xpm";
	asset[AR2].path = "./assets/entities/xpm/r2.xpm";
}

static void	xpm_map_paths(t_image *asset)
{
	asset[1].path = "./assets/map/xpm/1.xpm";
	asset[2].path = "./assets/map/xpm/2.xpm";
	asset[3].path = "./assets/map/xpm/3.xpm";
	asset[4].path = "./assets/map/xpm/4.xpm";
	asset[5].path = "./assets/map/xpm/52.xpm";
	asset[6].path = "./assets/map/xpm/6.xpm";
	asset[7].path = "./assets/map/xpm/7.xpm";
	asset[8].path = "./assets/map/xpm/8.xpm";
	asset[9].path = "./assets/map/xpm/9.xpm";
	asset[14].path = "./assets/map/xpm/14.xpm";
	asset[18].path = "./assets/map/xpm/18.xpm";
	asset[16].path = "./assets/map/xpm/16.xpm";
	asset[11].path = "./assets/map/xpm/11.xpm";
	asset[33].path = "./assets/map/xpm/33.xpm";
	asset[44].path = "./assets/map/xpm/44.xpm";
	asset[66].path = "./assets/map/xpm/66.xpm";
	asset[77].path = "./assets/map/xpm/77.xpm";
	asset[88].path = "./assets/map/xpm/88.xpm";
	asset[99].path = "./assets/map/xpm/99.xpm"; 
	asset[69].path = "./assets/map/xpm/69.xpm";
	asset[101].path = "./assets/map/xpm/101.xpm";
	asset[67].path = "./assets/map/xpm/67.xpm";
	asset[48].path = "./assets/map/xpm/0.xpm";
	asset[54].path = "./assets/map/xpm/54.xpm";
}

static void	img_sizes(t_image *asset)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		/*if (i == 4)
		{
			asset[i].height = 208/SCALER;
			asset[i].width = 128/SCALER;
		}*/
		if (i < 111)
		{
			asset[i].height = SIZE;
			asset[i].width = SIZE;
		}
		else
		{
			asset[i].height = SIZE/2;
			asset[i].width = SIZE/4;
		}
	}
}

static void	imgs_initializer(t_image *asset, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 128)
	{
		if (asset[i].path)
		{
			asset[i].img = mlx_xpm_file_to_image(mlx->mlx, 
				asset[i].path, &asset[i].width, &asset[i].height);
		}
	}
	i = -1;
	while (++i < 128)
	{
		if (asset[i].path)
		{
			asset[i].addr = mlx_get_data_addr(asset[i].img, 
				&asset[i].bpp, &asset[i].line_length, &asset[i].endian);
		}
	}
}

t_image *assets_initializer(t_mlx *mlx)
{
	int			i;
	t_image     *asset;

    asset = malloc(sizeof(t_image) * 128);
    if (!asset)
        return (NULL);
	i = -1;
	while (++i < 128)
		asset[i].path = NULL;
    xpm_map_paths(asset);
	xpm_entities_paths(asset);
	img_sizes(asset);
	imgs_initializer(asset, mlx);
    return (asset);
}