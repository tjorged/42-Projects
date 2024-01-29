#include "pipex.h"

void	file_name_checker(int argc, char **argv, t_cmd *cmd)
{
	int fd;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit (0);
	}
	close(fd);
}