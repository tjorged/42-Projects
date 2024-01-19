/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:58:42 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/22 08:58:44 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	collect_to_player(t_map *map, int y, int x, int *collect)
{
	if (map->collisions[y][x] == '0')
		map->collisions[y][x] = 'f';
	else if (map->collisions[y][x] == 'C')
	{
		map->collisions[y][x] = 'c';
		(*collect)++;
	}
	else if (map->collisions[y][x] == 'P')
		map->collisions[y][x] = 'p';
	else if (map->collisions[y][x] == 'E')
		map->collisions[y][x] = 'e';
	if (map->collisions[y][x + 1] == '0' 
	|| map->collisions[y][x + 1] == 'E' || map->collisions[y][x + 1] == 'C')
		collect_to_player(map, y, x + 1, collect);
	if (map->collisions[y + 1][x] == '0' 
	|| map->collisions[y + 1][x] == 'E' || map->collisions[y + 1][x] == 'C')
		collect_to_player(map, y + 1, x, collect);
	if (map->collisions[y][x - 1] == '0' 
	|| map->collisions[y][x - 1] == 'E' || map->collisions[y][x - 1] == 'C')
		collect_to_player(map, y, x - 1, collect);
	if (map->collisions[y - 1][x] == '0' 
	|| map->collisions[y - 1][x] == 'E' || map->collisions[y - 1][x] == 'C')
		collect_to_player(map, y - 1, x, collect);
}

static void	collect_to_exit(t_map *map, int y, int x, int *collect)
{
	if (map->collisions[y][x] == 'f')
		map->collisions[y][x] = '0';
	else if (map->collisions[y][x] == 'c')
	{
		map->collisions[y][x] = 'C';
		(*collect)++;
	}
	else if (map->collisions[y][x] == 'p')
		map->collisions[y][x] = 'P';
	else if (map->collisions[y][x] == 'e')
		map->collisions[y][x] = 'E';
	if (map->collisions[y][x + 1] == 'f' 
	|| map->collisions[y][x + 1] == 'p' || map->collisions[y][x + 1] == 'c')
		collect_to_exit(map, y, x + 1, collect);
	if (map->collisions[y + 1][x] == 'f' 
	|| map->collisions[y + 1][x] == 'p' || map->collisions[y + 1][x] == 'c')
		collect_to_exit(map, y + 1, x, collect);
	if (map->collisions[y][x - 1] == 'f' 
	|| map->collisions[y][x - 1] == 'p' || map->collisions[y][x - 1] == 'c')
		collect_to_exit(map, y, x - 1, collect);
	if (map->collisions[y - 1][x] == 'f' 
	|| map->collisions[y - 1][x] == 'p' || map->collisions[y - 1][x] == 'c')
		collect_to_exit(map, y - 1, x, collect);
}

static void	char_checker(t_map *map, int y, int x)
{
	int	exit;
	int	player;

	exit = 0;
	player = 0;
	while (map->collisions[++y] != NULL)
	{
		x = -1;
		while (map->collisions[y][++x] != '\n')
		{
			if (map->collisions[y][x] != '1' && map->collisions[y][x] != '0' 
			&& map->collisions[y][x] != 'C' && map->collisions[y][x] != 'E' 
			&& map->collisions[y][x] != 'P')
				delete_map(map->collisions, 'e');
			if (map->collisions[y][x] == 'C')
				map->collect++;
			if (map->collisions[y][x] == 'E')
				exit++;
			if (map->collisions[y][x] == 'P')
				player++;
		}
	}
	if (map->collect < 1 || exit != 1 || player != 1)
		delete_map(map->collisions, 'e');
}

static void	wall_checker(t_map *map, int y, int x, int max_y)
{
	while (y <= max_y)
	{
		if (map->collisions[y][0] != '1' \
		|| map->collisions[y][ft_strlen(map->collisions[y]) - 2] != '1')
			delete_map(map->collisions, 'e');
		if (y != max_y && ft_strlen(map->collisions[y]) \
		!= ft_strlen(map->collisions[y + 1]))
			delete_map(map->collisions, 'e');
		y++;
	}
	while (map->collisions[0][++x] != '\n')
	{
		if (map->collisions[0][x] != '1')
			delete_map(map->collisions, 'e');
	}
	x = -1;
	while (map->collisions[max_y][++x] != '\n')
	{
		if (map->collisions[max_y][x] != '1')
			delete_map(map->collisions, 'e');
	}
}

void	map_checker(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->collect = 0;
	wall_checker(map, 0, -1, (map->height - 1));
	map->width = ft_strlen(map->collisions[0]) - 1;
	char_checker(map, -1, -1);
	coord_finder(map);
	collect_to_player(map, map->player_y, map->player_x, &j);
	collect_to_exit(map, map->exit_y, map->exit_x, &i);
	if (j != map->collect || i != map->collect)
		delete_map(map->collisions, 'e');
}
