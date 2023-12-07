/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:27 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/04 15:48:24 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	end_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
	return (0);
}

int	keylog(int key, t_mlx *mlx)
{
	(void)mlx;
	printf("Pressed key: %d\n", key);
	return (0);
}



int main()
{
	t_mlx		mlx;
	t_asset		back;
	
 	back.path = "./assets/map/teste.xpm";
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	mlx.window = mlx_new_window(mlx.mlx, 1920, 1080, "so_long");
	if (!mlx.window)
		return (free(mlx.mlx), 1);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, &keylog, &mlx);
	back.img = mlx_xpm_file_to_image(mlx.mlx, back.path, &back.w, &back.h);
	mlx_put_image_to_window(mlx.mlx, mlx.window, back.img, 0, 0);
	mlx_hook(mlx.window, DestroyNotify, StructureNotifyMask, &end_mlx, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
