#include "so_long.h"

static void xpm_entities_paths(t_image *asset)
{
    asset[au].path = "./assets/map/u.xpm";
	asset[au1].path = "./assets/map/u1.xpm";
	asset[au2].path = "./assets/map/u2.xpm";
	asset[ad].path = "./assets/map/d.xpm";
	asset[ad1].path = "./assets/map/d1.xpm";
	asset[ad2].path = "./assets/map/d2.xpm";
	asset[al].path = "./assets/map/l.xpm";
	asset[al1].path = "./assets/map/l1.xpm";
	asset[al2].path = "./assets/map/l2.xpm";
	asset[ar].path = "./assets/map/r.xpm";
	asset[ar1].path = "./assets/map/r1.xpm";
	asset[ar2].path = "./assets/map/r2.xpm";
}

static void	xpm_map_paths(t_image *asset)
{
	asset[a1].path = "./assets/map/1.xpm";
	asset[a2].path = "./assets/map/2.xpm";
	asset[a3].path = "./assets/map/3.xpm";
	asset[a4].path = "./assets/map/4.xpm";
	asset[a5].path = "./assets/map/5.xpm";
	asset[a6].path = "./assets/map/6.xpm";
	asset[a7].path = "./assets/map/7.xpm";
	asset[a8].path = "./assets/map/8.xpm";
	asset[a9].path = "./assets/map/9.xpm";
	asset[a14].path = "./assets/map/14.xpm";
	asset[a18].path = "./assets/map/18.xpm";
	asset[a16].path = "./assets/map/16.xpm";
	asset[a11].path = "./assets/map/11.xpm";
	asset[a33].path = "./assets/map/33.xpm";
	asset[a44].path = "./assets/map/44.xpm";
	asset[a66].path = "./assets/map/66.xpm";
	asset[a77].path = "./assets/map/77.xpm";
	asset[a88].path = "./assets/map/88.xpm";
	asset[a99].path = "./assets/map/99.xpm"; 
	asset[aE].path = "./assets/map/E.xpm";
	asset[ae].path = "./assets/map/e.xpm";
	asset[aC].path = "./assets/map/C.xpm";
	asset[a0].path = "./assets/map/0.xpm";
}

static void	img_sizes(t_image *asset)
{
	int	i;

	i = 0;
	while (++i < 35)
	{
		if (i == 4)
		{
			asset[i].height = 208/2;
			asset[i].width = 128/2;
		}
		else if (i <= 22)
		{
			asset[i].height = 128/2;
			asset[i].width = 128/2;
		}
		else
		{
			asset[i].height = 64/2;
			asset[i].width = 32/2;
		}
	}
}

static void	imgs_initializer(t_image *asset, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 35)
	{
		asset[i].img = mlx_xpm_file_to_image(mlx->mlx, 
				asset[i].path, &asset[i].width, &asset[i].height);
		printf("path[%i] = %s\n", i, asset[i].path);
	}
	i = -1;
	while (++i < 36)
	{
		asset[i].addr = mlx_get_data_addr(asset[i].img, 
			&asset[i].bpp, &asset[i].line_length, &asset[i].endian);
		printf("address[%i] = %p\n", i, &asset[i].addr);
	}
}

t_image *assets_initializer(t_mlx *mlx)
{
    t_image     *asset;

    asset = malloc(sizeof(t_image) * 35);
    if (!asset)
        return (NULL);
    xpm_map_paths(asset);
	xpm_entities_paths(asset);
	img_sizes(asset);
	imgs_initializer(asset, mlx);
	printf("OI!\n");
    return (asset);
}