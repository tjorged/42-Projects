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

void 	render(t_mlx *mlx, t_frame *frame)
{
	int		y;
	int		x;

	y = 0;
	while (y < mlx->map->height * SIZE)
	{
		x = 0;
		while (x < mlx->map->width * SIZE)
		{
			my_mlx_pixel_put(&frame->frame, x, y, 
			get_color(&frame->back,  x, y));
			if (x >= frame->player_x && x < frame->player_x + (SIZE/4) 
			&& y >= frame->player_y && y < frame->player_y + (SIZE/2))
			{
				my_mlx_pixel_put(&frame->frame, x, y, get_color(&frame->player, 
				(x -frame->player_x) * SCALER, (y - frame->player_y) * SCALER));
			} 
			my_mlx_pixel_put(&frame->frame, x, y, 
			get_color(&frame->front,  x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, frame->frame.img, 0, 0);
}