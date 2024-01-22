/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:46:58 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/12/19 12:35:04 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	file_name_checker(char *file)
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
		write(2, "Error\n", 6);
		ft_printf("Snake, that map has an invalid name.\n");
		exit(0);
	}
}

static int	row_counter(char *file)
{
	int		i;
	int		fd;
	char	*row;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		ft_printf("Snake, that map does not exist.\n");
		exit(0);
	}
	row = get_next_line(fd);
	while (row != NULL)
	{
		free(row);
		i++;
		row = get_next_line(fd);
	}
	free(row);
	close(fd);
	return (i);
}

static void	row_creator(t_map *map, char *file)
{
	int	i;
	int	fd;

	i = -1;
	fd = open(file, O_RDONLY);
	while (++i < map->height)
	{
		map->collisions[i] = get_next_line(fd);
		if (!map->collisions[i])
			delete_map(map->collisions, 'c');
	}
	close(fd);
}

static void	map_transformer(t_map *map)
{
	int	j;

	j = -1;
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!(map->map))
		delete_map(map->collisions, 'c');
	map->map[map->height] = NULL;
	while (++j < map->height)
	{
		map->map[j] = ft_strdup(map->collisions[j]);
		if (!(map->map[j]))
		{
			delete_map(map->collisions, '0');
			delete_map(map->map, 'c');
		}
	}
	transform(map, 0, 0);
}

void	**mapper(char *file, t_map *map)
{
	map->collect = 0;
	file_name_checker(file);
	map->height = row_counter(file);
	if (map->height == 0)
	{
		write (2, "Error\n", 6);
		ft_printf("Do you expect me to read an empty intel Snake?\n");
		exit(0);
	}
	map->collisions = malloc(sizeof(char *) * (map->height + 1));
	if (!map->collisions)
		exit(0);
	map->collisions[map->height] = NULL;
	row_creator(map, file);
	map_checker(map);
	map_transformer(map);
	return (NULL);
}
