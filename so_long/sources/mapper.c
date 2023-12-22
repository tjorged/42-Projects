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
		write(2, "INVALID MAP NAME SNAKE!\n", 24);
		exit(0);
	}
	
}

static int	row_counter(char *file)
{
	int	i;
	int	fd;
	char 	*row;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Snake, that map does not exist\n", 31);
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
	if (i == 0)
		exit (0);
	return (i);
}

static void	row_creator(t_map *map, char *file)
{
	int	i;
	int	fd;
	
	i = -1;
	fd = open(file, O_RDONLY);
	while (++i < map->row_count)
	{
		map->collisions[i] = get_next_line(fd);
		if (!map->collisions[i])
			delete_map(map->collisions, 'e');
	}
	close(fd);
}

void	**mapper(char *file, t_map *map)
{
	char 	*row;
	
	file_name_checker(file);
	map->row_count = row_counter(file);
	map->collisions = (char **)malloc(sizeof(char*) * (map->row_count + 1));
	if (!map->collisions)
		exit(0);
	map->collisions[map->row_count] = NULL;
	row_creator(map, file);
	map_checker(map);
	map_transformer(map);
	delete_map(map->collisions, 'a');
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int	j;
	int	i;
	t_map	map;
	
	map.collect = 0;
	mapper(argv[1], &map);
	j = -1;
	while (map.map[++j])
	{
		i = -1;
		while (map.map[j][++i] != '\n')
		{
			if(map.map[j][i] < 10)
				printf("%i    ", map.map[j][i]);
			else if(map.map[j][i] < 100)
				printf("%i   ", map.map[j][i]);
			else
				printf("%i  ", map.map[j][i]);
		}
		printf("\n");
	}
	delete_map(map.map, 'a');
}
