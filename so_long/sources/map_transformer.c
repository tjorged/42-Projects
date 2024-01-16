/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:01:55 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/22 14:01:59 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	corners(t_map *map, int y, int x)
{
	if (map->collisions[y][x] == '1' && map->collisions[y - 1][x] == '1' 
	&& ground(map->map[y - 1][x + 1]) && map->collisions[y][x - 1] == '1' 
	&& map->collisions[y - 1][x - 1] == '1' && map->collisions[y][x + 1] == '1'
	&& map->collisions[y + 1][x - 1] == '1' && map->collisions[y + 1][x] == '1' 
	&& map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 1;
	else if (ground(map->map[y - 1][x - 1]) && map->collisions[y - 1][x] == '1' 
	&& map->collisions[y - 1][x + 1] == '1' && map->collisions[y][x - 1] == '1' 
	&& map->collisions[y][x] == '1' && map->collisions[y][x + 1] == '1'
	&& map->collisions[y + 1][x - 1] == '1' && map->collisions[y + 1][x] == '1' 
	&& map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 3;
	else if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y - 1][x] == '1' && map->collisions[y - 1][x + 1] == '1' 
	&& map->collisions[y][x - 1] == '1' && map->collisions[y][x] == '1' 
	&& map->collisions[y][x + 1] == '1' && map->collisions[y + 1][x - 1] == '1' 
	&& map->collisions[y + 1][x] == '1' && ground(map->map[y + 1][x + 1]))
		map->map[y][x] = 7;
	else if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y - 1][x] == '1' && map->collisions[y - 1][x + 1] == '1' 
	&& map->collisions[y][x - 1] == '1' && map->collisions[y][x] == '1' 
	&& map->collisions[y][x + 1] == '1' && ground(map->map[y + 1][x - 1]) 
	&& map->collisions[y + 1][x] == '1' && map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 9;
}

void	inner_corners2(t_map *map, int y, int x)
{
	if ((map->map[y + 1][x] == 6 || map->map[y + 1][x] == 11 \
		|| map->map[y + 1][x] == 3) \
		&& (map->map[y][x + 1] == 2 || map->map[y][x + 1] == 99 \
		|| map->map[y][x + 1] == 3))
		map->map[y][x] = 77;
	else if ((map->map[y + 1][x] == 4 || map->map[y + 1][x] == 33 \
		|| map->map[y + 1][x] == 1) \
		&& (map->map[y][x - 1] == 2 || map->map[y][x - 1] == 77 \
		|| map->map[y][x - 1] == 1))
		map->map[y][x] = 99;
	else if ((map->map[y][x - 1] == 8 || map->map[y][x - 1] == 11 \
		|| map->map[y][x - 1] == 7) \
		&& (map->map[y - 1][x] == 4 || map->map[y - 1][x] == 99 \
		|| map->map[y - 1][x] == 7))
		map->map[y][x] = 33;
	else if ((map->map[y - 1][x] == 6 || map->map[y - 1][x] == 77 \
		|| map->map[y - 1][x] == 9) \
		&& (map->map[y][x + 1] == 8 || map->map[y][x + 1] == 33 \
		|| map->map[y][x + 1] == 9))
		map->map[y][x] = 11;
}

void	inner_corners(t_map *map, int y, int x)
{
	if (map->collisions[y - 1][x] == '1' 
	&& map->collisions[y - 1][x + 1] == '1' && ground(map->map[y][x - 1]) 
	&& map->collisions[y][x] == '1' && map->collisions[y][x + 1] == '1'
	&& ground(map->map[y + 1][x - 1]) && ground(map->map[y + 1][x]))
		map->map[y][x] = 11;
	else if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y - 1][x] == '1' && map->collisions[y][x - 1] == '1' 
	&& map->collisions[y][x] == '1' && ground(map->map[y][x + 1])
	&& ground(map->map[y + 1][x]) && ground(map->map[y + 1][x + 1]))
		map->map[y][x] = 33;
	else if (ground(map->map[y - 1][x]) && ground(map->map[y - 1][x + 1])
	&& map->collisions[y][x - 1] == '1' && map->collisions[y][x] == '1' 
	&& ground(map->map[y][x + 1]) && map->collisions[y + 1][x - 1] == '1' 
	&& map->collisions[y + 1][x] == '1')
		map->map[y][x] = 99;
	else if (ground(map->map[y - 1][x - 1]) && ground(map->map[y - 1][x]) 
	&& ground(map->map[y][x - 1]) && map->collisions[y][x] == '1' 
	&& map->collisions[y][x + 1] == '1' && map->collisions[y + 1][x] == '1' 
	&& map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 77;
}

static void	borders2(t_map *map, int y, int x)
{
	while (x >= 0)
	{
		if (ground(map->map[y - 1][x]))
			map->map[y][x] = 2;
		else if (map->map[y - 1][x] == 6 || map->map[y - 1][x] == 77)
			map->map[y][x] = 3;
		else if (map->map[y - 1][x] == 4 || map->map[y - 1][x] == 99)
			map->map[y][x] = 1;
		x--;
	}
	x++;
	while (y >= 0)
	{
		if (ground(map->map[y][x + 1]))
			map->map[y][x] = 4;
		else if (map->map[y][x + 1] == 2 || map->map[y][x + 1] == 99)
			map->map[y][x] = 1;
		else if (map->map[y][x + 1] == 8 || map->map[y][x + 1] == 33)
			map->map[y][x] = 7;
		y--;
	}
}

void	borders(t_map *map, int y, int x)
{
	while (x < map->width)
	{
		if (ground(map->map[y + 1][x]))
			map->map[y][x] = 8;
		else if (map->map[y + 1][x] == 4 || map->map[y + 1][x] == 33)
			map->map[y][x] = 7;
		else if (map->map[y + 1][x] == 6 || map->map[y + 1][x] == 11)
			map->map[y][x] = 9;
		x++;
	}
	x--;
	while (y < map->height)
	{
		if (ground(map->map[y][x - 1]))
			map->map[y][x] = 6;
		else if (map->map[y][x - 1] == 8 || map->map[y][x - 1] == 11)
			map->map[y][x] = 9;
		else if (map->map[y][x - 1] == 2 || map->map[y][x - 1] == 77)
			map->map[y][x] = 3;
		y++;
	}
	y--;
	borders2(map, y, x);
}
