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
