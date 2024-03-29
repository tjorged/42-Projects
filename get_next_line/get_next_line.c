/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tjorge-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:07:27 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/08 17:23:28 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		ft_zeros(buffer, 'c');
		return (NULL);
	}
	new_line = ft_line_creator(buffer, fd);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}

int	main(void)
{
	printf("LINHA: %s", get_next_line(0));
	/*fd = open("tes.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("1st: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("2nd: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("3rd: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("4th: %s", line);
	free(line);
	close(fd);*/
	return (0);
}
