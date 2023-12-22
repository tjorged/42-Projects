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

static void	function_caller()
{
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (flor(map->map[j][i]))
				walls(map, j, i);
		}
	}
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (flor(map->map[j][i]))
				corners(map, j, i);
		}
	}
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (!(flor(map->map[j][i])))
				singles(map, j, i);
		}
	}
}

static void	walls(t_map *map, int y, int x)
{
	if (map->collisions[y][x + 1] == '1')
		map->map[y][x + 1] = 6;
	if (map->collisions[y + 1][x] == '1')
		map->map[y + 1][x] = 2;
	if (map->collisions[y][x - 1] == '1')
		map->map[y][x - 1] = 4;
	if (map->collisions[y - 1][x] == '1')
		map->map[y - 1][x] = 8;
}

static void	corners(t_map *map, int y, int x)
{
	if (map->collisions[y - 1][x + 1] == '1' 
	&& map->collisions[y][x + 1] == '1' && map->collisions[y - 1][x] == '1')
		map->map[y - 1][x + 1] = 9;
	if (map->collisions[y + 1][x + 1] == '1' 
	&& map->collisions[y + 1][x] == '1' && map->collisions[y][x + 1] == '1') 
		map->map[y + 1][x + 1] = 3;
	if (map->collisions[y + 1][x - 1] == '1' 
	&& map->collisions[y][x - 1] == '1' && map->collisions[y + 1][x] == '1') 
		map->map[y + 1][x - 1] = 1;
	if (map->collisions[y - 1][x - 1] == '1' 
	&& map->collisions[y][x - 1] == '1' && map->collisions[y - 1][x] == '1')
		map->map[y - 1][x - 1] = 7;
	if (map->collisions[y - 1][x + 1] == '1' 
	&& flor(map->collisions[y][x + 1]) && flor(map->collisions[y - 1][x]))
		map->map[y - 1][x + 1] = 99;
	if (map->collisions[y + 1][x + 1] == '1' 
	&& flor(map->collisions[y + 1][x]) && flor(map->collisions[y][x + 1]))
		map->map[y + 1][x + 1] = 77;
	if (map->collisions[y + 1][x - 1] == '1' 
	&& flor(map->collisions[y][x - 1]) && flor(map->collisions[y + 1][x]))
		map->map[y + 1][x - 1] = 11;
	if (map->collisions[y - 1][x - 1] == '1' 
	&& flor(map->collisions[y][x - 1]) && flor(map->collisions[y - 1][x]))
		map->map[y - 1][x - 1] = 33;
}

static void	singles(t_map *map, int y, int x)
{
	int	corners;
	int	sides;
	
	corners = 0;
	sides = 0;
	if (x + 1 == '\n' || x - 1 == -1 || y - 1 == -1 || y + 1 == map->row_count)
		return ;
	if (flor(map->collisions[y][x + 1]))
		sides++;
	if (flor(map->collisions[y][x - 1]))
		sides++;
	if (flor(map->collisions[y + 1][x]))
		sides++;
	if (flor(map->collisions[y - 1][x]))
		sides++;
	if (flor(map->collisions[y + 1][x + 1]))
		corners++;
	if (flor(map->collisions[y - 1][x - 1]))
		corners++;
	if (flor(map->collisions[y + 1][x - 1]))
		corners++;
	if (flor(map->collisions[y - 1][x + 1]))
		corners++;
	singles_handler(&map->map[y][x], corners, sides);
}

void	map_transformer(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	map->map = (char **)malloc(sizeof(char*) * (map->row_count + 1));
	map->collisions[map->row_count] = NULL;
	while (++j < map->row_count)
		map->map[j] = ft_strdup(map->collisions[j]);
	j = -1;
	if (!map->map)
		delete_map(map->collisions, 'e');
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (flor(map->map[j][i]))
				walls(map, j, i);
		}
	}
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (flor(map->map[j][i]))
				corners(map, j, i);
		}
	}
	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i] != '\n')
		{
			if (!(flor(map->map[j][i])))
				singles(map, j, i);
		}
	}
}
