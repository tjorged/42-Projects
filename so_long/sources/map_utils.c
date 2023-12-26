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

void	coord_finder(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (map->collisions[++j] != NULL)
	{
		i = -1;
		while (map->collisions[j][++i] != '\0')
		{
			if (map->collisions[j][i] == 'P')
			{
				map->player_y = j;
				map->player_x = i;
			}
			if (map->collisions[j][i] == 'E')
			{
				map->exit_y = j;
				map->exit_x = i;
			}
		}
	}
}

int	ground(char current, int mode)
{
	if (mode == 1 && (current == '0' 
			|| current == 'C' 
			|| current == 'E' 
			|| current == 'P'))
		return (1);
	if (mode == 2 && (current == '0' 
			|| current == 'C' 
			|| current == 'E' 
			|| current == 'P' 
			|| current == 5))
		return (1);
	return (0);
}

void	inner_corners(t_map *map, int y, int x)
{
	if (map->map[y + 1][x] == 6 && (map->map[y][x + 1] == 2 
	|| map->map[y][x + 1] == 5 || map->map[y][x + 1] == 11))
		map->map[y][x] = 77;
	if (map->map[y][x + 1] == 2 && (map->map[y + 1][x] == 6 
	|| map->map[y + 1][x] == 5 || map->map[y + 1][x] == 99))
		map->map[y][x] = 77;
	if (map->map[y - 1][x] == 6 && (map->map[y][x + 1] == 8 
	|| map->map[y][x + 1] == 5 || map->map[y][x + 1] == 33))
		map->map[y][x] = 11;
	if (map->map[y][x + 1] == 8 && (map->map[y - 1][x] == 6 
	|| map->map[y - 1][x] == 5 || map->map[y - 1][x] == 77))
		map->map[y][x] = 11;
	if (map->map[y][x - 1] == 8 && (map->map[y - 1][x] == 4 
	|| map->map[y - 1][x] == 5 || map->map[y - 1][x] == 99))
		map->map[y][x] = 33;
	if (map->map[y - 1][x] == 4 && (map->map[y][x - 1] == 8 
	|| map->map[y][x - 1] == 5 || map->map[y][x - 1] == 11))
		map->map[y][x] = 33;
	if (map->map[y + 1][x] == 4 && (map->map[y][x - 1] == 2 
	|| map->map[y][x - 1] == 5 || map->map[y][x - 1] == 77))
		map->map[y][x] = 99;
	if (map->map[y][x - 1] == 2 && (map->map[y + 1][x] == 4 
	|| map->map[y + 1][x] == 5 || map->map[y + 1][x] == 33))
		map->map[y][x] = 99;
}
