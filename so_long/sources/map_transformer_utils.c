/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:11:20 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/22 13:11:28 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ground(char current)
{
	if (current == '0' 
		|| current == 'C' 
		|| current == 'E' 
		|| current == 'P' 
		|| current == 5)
		return (1);
	else
		return (0);
}

static void	walls(t_map *map, int y, int x)
{
	if (ground(map->map[y - 1][x]) && map->collisions[y][x - 1] == '1' 
	&& map->collisions[y][x] == '1' && map->collisions[y][x + 1] == '1'
	&& map->collisions[y + 1][x - 1] == '1' 
	&& map->collisions[y + 1][x] == '1' && map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 2;
	else if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y - 1][x] == '1' && map->collisions[y][x - 1] == '1' 
	&& map->collisions[y][x] == '1' && ground(map->map[y][x + 1]) 
	&& map->collisions[y + 1][x - 1] == '1' && map->collisions[y + 1][x] == '1')
		map->map[y][x] = 4;
	else if (map->collisions[y - 1][x] == '1' 
	&& map->collisions[y - 1][x + 1] == '1' && ground(map->map[y][x - 1]) 
	&& map->collisions[y][x] == '1' && map->collisions[y][x + 1] == '1' 
	&& map->collisions[y + 1][x] == '1' && map->collisions[y + 1][x + 1] == '1')
		map->map[y][x] = 6;
	else if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y - 1][x] == '1' && map->collisions[y - 1][x + 1] == '1' 
	&& map->collisions[y][x - 1] == '1' && map->collisions[y][x] == '1' 
	&& map->collisions[y][x + 1] == '1' && ground(map->map[y + 1][x]))
		map->map[y][x] = 8;
}

static void	doors(t_map *map, int y, int x)
{
	if ((map->collisions[y][x] == 'E' || map->collisions[y][x] == 'P') 
	&& map->map[y - 1][x] == 8)
	{
		map->map[y][x] = '0';
		map->map[y - 1][x] = 88;
	}
	else if ((map->collisions[y][x] == 'E' || map->collisions[y][x] == 'P') 
	&& map->map[y][x + 1] == 6)
	{
		map->map[y][x] = '0';
		map->map[y][x + 1] = 66;
	}
	else if ((map->collisions[y][x] == 'E' || map->collisions[y][x] == 'P') 
	&& map->map[y][x - 1] == 4)
	{
		map->map[y][x] = '0';
		map->map[y][x - 1] = 44;
	}
	else if (map->collisions[y][x] == 'P')
		map->map[y][x] = 'E';
}

static void	singles(t_map *map, int y, int x)
{
	while (++y < (map->height - 1))
	{
		x = 0;
		while (++x < (map->width - 1))
		{
			if (map->collisions[y][x] == '1' 
			&& !((map->collisions[y - 1][x - 1] == '1' 
			&& map->collisions[y - 1][x] == '1'
			&& map->collisions[y][x - 1] == '1' \
			&& map->collisions[y][x] == '1') 
			|| (map->collisions[y - 1][x] == '1' 
			&& map->collisions[y - 1][x + 1] == '1'
			&& map->collisions[y][x] == '1' \
			&& map->collisions[y][x + 1] == '1') 
			|| (map->collisions[y][x - 1] == '1' \
			&& map->collisions[y][x] == '1' 
			&& map->collisions[y + 1][x - 1] == '1' 
			&& map->collisions[y + 1][x] == '1') 
			|| (map->collisions[y][x] == '1' && map->collisions[y][x + 1] == '1'
			&& map->collisions[y + 1][x] == '1' 
			&& map->collisions[y + 1][x + 1] == '1')))
				map->map[y][x] = 5;
		}
	}
}

void	transform(t_map *map, int y, int x)
{
	singles(map, 0, 0);
	while (++y < (map->height - 1))
	{
		x = 0;
		while (++x < (map->width - 1))
		{
			walls(map, y, x);
			corners(map, y, x);
			inner_corners(map, y, x);
		}
	}
	y = 0;
	while (++y < (map->height - 1))
	{
		x = 0;
		while (++x < (map->width - 1))
			inner_corners2(map, y, x);
	}
	borders(map, 0, 0);
	borders_refiner(map, 0, 1);
	doors(map, map->exit_y, map->exit_x);
	doors(map, map->player_y, map->player_x);
}
