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

//static void	map_transformer()

static int	row_counter(char *file)
{
	int	i;
	int	fd;
	char 	*row;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		write(2, "Snake, that map does not exist")
	row = get_next_line(fd);
	while (row != NULL)
	{
		free(row);
		i++;
		row = get_next_line(fd);
	}
	free(row);
	close(fd);
	printf("i = %i\n", i);
	if (i == 0)
		exit (0);
	return (i);
}

static void	row_creator(char **map, char *file, int max)
{
	int	i;
	int	fd;
	
	i = -1;
	fd = open(file, O_RDONLY);
	while (++i < max)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			delete_map(map, 'e');
	}
	close(fd);
	printf("i = %i\n", i);
}

void	**mapper(char *file, t_map *info)
{
	int	i;
	char 	*row;
	char	**map;
	
	file_name_checker(file);
	i = row_counter(file);
	map = (char **)malloc(sizeof(char*) * (i + 1));
	if (!map)
		exit(0);
	map[i] = NULL;
	row_creator(map, file, i);
	wall_checker(map, 0, -1, (i - 1));
	char_checker(map, -1, -1, info);
//	map_transformer(map);
	delete_map(map, 'a');
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_map	map;
	
	map.collect = 0;
	mapper(argv[1], &map);
	printf("collectibles = %i", map.collect);
}
