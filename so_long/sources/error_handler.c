/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:33:15 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/19 16:10:19 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	char_checker(char **map, int y, int x, t_map *info)
{
	int	exit;
	int	player;
	
	exit = 0;
	player = 0;
	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != '\n')
		{
			if (map[y][x] != '1' && map[y][x] != '0' 
			&& map[y][x] != 'C' && map[y][x] != 'E' 
			&& map[y][x] != 'P')
				delete_map(map, 'e');
			if (map[y][x] == 'C')
				info->collect++;
			if (map[y][x] == 'E')
				exit++;
			if (map[y][x] == 'P')
				player++;
		}
	}
	if (info->collect < 1 || exit != 1 || player != 1)
		delete_map(map, 'e');
}

void	wall_checker(char **map, int y, int x, int max_y)
{
	while (y <= max_y)
	{
		if (map[y][0] != '1' || map[y][ft_strlen(map[y]) - 2] != '1')
			delete_map(map, 'e');
		if (y != max_y && ft_strlen(map[y]) != ft_strlen(map[y + 1]))
			delete_map(map, 'e');
		y++;
	}
	while (map[0][++x] != '\n')
	{
		if (map[0][x] != '1')
			delete_map(map, 'e');
	}
	x = -1;
	
	while (map[max_y][++x] != '\n')
	{
		if (map[max_y][x] != '1')
			delete_map(map, 'e');
	}
}

void	file_name_checker(char *file)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	i = ft_strlen(file);
	if (file[--i] != 'r')
		error = 1;
	if (file[--i] != 'e')
		error = 1;
	if (file[--i] != 'b')
		error = 1;
	if (file[--i] != '.')
		error = 1;
	if (file[--i] == '/')
		error = 1;
	if (error)
	{
		write(2, "INVALID MAP NAME SNAKE!\n", 24);
		exit(0);
	}
	
}

void	delete_map(char **map, char mode)
{
	int	i;
	
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	if (mode == 'e')
	{
		write(2, "INVALID MAP SNAKE!\n", 19);
		exit(0);
	}
}
