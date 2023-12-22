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

int	flor(char current)
{
	if (current == '0' || current == 'C' 
	|| current == 'E' || current == 'P')
		return (1);
	return (0);
}

void	singles_handler(char *current, int corners, int sides)
{
	if (corners + sides == 8)
		(*current) = 5;
	else if (corners == 4)
		(*current) = 5;
	else if (sides == 4)
		(*current) = 5;
	else if (sides == 2 && corners == 2)
		(*current) = 5;
	else if (((*current) == 1 || (*current) == 7) && corners == 2)
		(*current) = 4;
	else if (((*current) == 3 || (*current) == 9) && corners == 2)
		(*current) = 6;
	else if (((*current) == 7 || (*current) == 9) && corners == 2)
		(*current) = 8;
	else if (((*current) == 1 || (*current) == 3) && corners == 2)
		(*current) = 2;
}

