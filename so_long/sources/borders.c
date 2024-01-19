/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:49:47 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:49:49 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	borders_refiner4(t_map *map, int y, int x)
{
	while (y > 0)
	{
		if (map->map[y][x] == '1' && map->map[y][x + 1] == '1' \
		&& ground(map->map[y - 1][x + 1]))
		{
			map->map[y][x] = 1;
			map->map[y][x + 1] = 99;
		}
		else if (map->map[y][x] == '1' && map->map[y][x + 1] == '1' \
		&& ground(map->map[y + 1][x + 1]))
		{
			map->map[y][x] = 7;
			map->map[y][x + 1] = 33;
		}
		y--;
	}
}

static void	borders_refiner3(t_map *map, int y, int x)
{
	while (x > 0)
	{
		if (map->map[y][x] == '1' && map->map[y - 1][x] == '1' \
		&& ground(map->map[y - 1][x - 1]))
		{
			map->map[y][x] = 3;
			map->map[y - 1][x] = 77;
		}
		else if (map->map[y][x] == '1' && map->map[y - 1][x] == '1' \
		&& ground(map->map[y - 1][x + 1]))
		{
			map->map[y][x] = 1;
			map->map[y - 1][x] = 99;
		}
		x--;
	}
	x++;
	borders_refiner4(map, map->height - 2, 0);
}

static void	borders_refiner2(t_map *map, int y, int x)
{
	while (y < map->height - 1)
	{
		if (map->map[y][x] == '1' && map->map[y][x - 1] == '1' \
		&& ground(map->map[y - 1][x - 1]))
		{
			map->map[y][x] = 3;
			map->map[y][x - 1] = 77;
		}
		else if (map->map[y][x] == '1' && map->map[y][x - 1] == '1' \
		&& ground(map->map[y + 1][x - 1]))
		{
			map->map[y][x] = 9;
			map->map[y][x - 1] = 11;
		}
		y++;
	}
	y--;
	borders_refiner3(map, map->height - 1, map->width - 2);
}

void	borders_refiner(t_map *map, int y, int x)
{
	while (x < map->width - 1)
	{
		if (map->map[y][x] == '1' && map->map[y + 1][x] == '1' \
		&& ground(map->map[y + 1][x - 1]))
		{
			map->map[y][x] = 9;
			map->map[y + 1][x] = 11;
		}
		else if (map->map[y][x] == '1' && map->map[y + 1][x] == '1' \
		&& ground(map->map[y + 1][x + 1]))
		{
			map->map[y][x] = 7;
			map->map[y + 1][x] = 33;
		}
		x++;
	}
	x--;
	borders_refiner2(map, 1, map->width - 2);
}
