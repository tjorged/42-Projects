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

static void	walls_n_doors(t_map *map, int y, int x, char mode)
{
	if (mode == 'w')
	{
		if (map->map[y][x + 1] == '1')
			map->map[y][x + 1] = 6;
		if (map->map[y + 1][x] == '1')
			map->map[y + 1][x] = 2;
		if (map->map[y][x - 1] == '1')
			map->map[y][x - 1] = 4;
		if (map->map[y - 1][x] == '1')
			map->map[y - 1][x] = 8;
	}
	if (mode == 'd')
	{
		map->map[y][x] = '0';
		if (map->map[y - 1][x] == 8)
			map->map[y - 1][x] = 88;
		else if (map->map[y][x + 1] == 6)
			map->map[y][x + 1] = 66;
		else if (map->map[y][x - 1] == 4)
			map->map[y][x - 1] = 44;
		else
			map->map[y][x] = 55;
	}
}

static void	corners(t_map *map, int y, int x)
{
	if (map->collisions[y][x + 1] == '\n' || x - 1 == -1 
	|| y - 1 == -1 || y + 1 == map->height)
		return ;
	if (map->map[y][x] == 5 && map->map[y][x + 1] == '1')
		map->map[y][x + 1] = 6;
	if (map->map[y][x] == 5 && map->map[y - 1][x] == '1')
		map->map[y - 1][x] = 8;
	if (map->map[y][x] == 5 && map->map[y][x - 1] == '1')
		map->map[y][x - 1] = 4;
	if (map->map[y][x] == 5 && map->map[y + 1][x] == '1')
		map->map[y + 1][x] = 2;
	if (map->map[y - 1][x] == 8 && map->map[y][x + 1] == 6)
		map->map[y - 1][x + 1] = 9;
	if (map->map[y - 1][x] == 8 && map->map[y][x - 1] == 4)
		map->map[y - 1][x - 1] = 7;
	if (map->map[y + 1][x] == 2 && map->map[y][x - 1] == 4)
		map->map[y + 1][x - 1] = 1;
	if (map->map[y + 1][x] == 2 && map->map[y][x + 1] == 6)
		map->map[y + 1][x + 1] = 3;
	if (map->map[y][x] == 5)
		inner_corners(map, y, x);
}

static void	singles(t_map *map, int y, int x)
{
	int	walkables;

	walkables = 0;
	if (map->collisions[y][x + 1] == '\n' || x - 1 == -1 
	|| y - 1 == -1 || y + 1 == map->height)
		return ;
	if (ground(map->collisions[y][x + 1], 1))
		walkables++;
	if (ground(map->collisions[y][x - 1], 1))
		walkables++;
	if (ground(map->collisions[y + 1][x], 1))
		walkables++;
	if (ground(map->collisions[y - 1][x], 1))
		walkables++;
	if (ground(map->collisions[y + 1][x + 1], 1))
		walkables++;
	if (ground(map->collisions[y - 1][x - 1], 1))
		walkables++;
	if (ground(map->collisions[y + 1][x - 1], 1))
		walkables++;
	if (ground(map->collisions[y - 1][x + 1], 1))
		walkables++;
	if (walkables > 3)
		map->map[y][x] = 5;
}

static void	function_caller(t_map *map, int i, int j, int counter)
{
	while (++counter < 4)
	{
		j = -1;
		while (map->map[++j])
		{
			i = -1;
			while (counter == 1 && map->map[j][++i] != '\n')
			{
				if (ground(map->map[j][i], 2))
					walls_n_doors(map, j, i, 'w');
			}
			while (counter == 2 && map->map[j][++i] != '\n')
			{
				if (map->collisions[j][i] == '1')
					singles(map, j, i);
			}
			while (counter == 3 && map->map[j][++i] != '\n')
				corners(map, j, i);
		}
	}
}

void	map_transformer(t_map *map)
{
	int	j;

	j = -1;
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!(map->map))
		delete_map(map->collisions, 'e');
	map->collisions[map->height] = NULL;
	while (++j < map->height)
	{
		map->map[j] = ft_strdup(map->collisions[j]);
		if (!(map->map[j]))
		{
			delete_map(map->collisions, '0');
			delete_map(map->map, 'e');
		}
	}
	function_caller(map, -1, -1, 0);
	walls_n_doors(map, map->exit_y, map->exit_x, 'd');
	walls_n_doors(map, map->player_y, map->player_x, 'd');
}
