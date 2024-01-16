#include "so_long.h"

void    coord_finder(t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
		{
    		if (map->collisions[j][i] == 'E')
			{
				map->exit_y = j;
				map->exit_x = i;
			}
			if (map->collisions[j][i] == 'P')
			{
				map->player_y = j;
				map->player_x = i;
			}
		}
	}
}