#include "pipex.h"

void free_n_exit(t_cmd *cmd)
{
	perror(0);
	free_cmd(cmd);
	exit(0);	
}

void free_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (i == 0)
			free((paths[i] - 5));
		else
			free(paths[i]);
	}
	free(paths);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	j = -1;
	while (++j <= cmd[0].process_nb)
	{
		i = 0;
		while (cmd[j].arg[i] != NULL)
		{
			if (cmd[j].arg[i])
				free(cmd[j].arg[i]);
			i++;
		}
		if (cmd[j].arg)
			free(cmd[j].arg);
		if (j != 0 && cmd[j].path)
			free(cmd[j].path);
	}
	free(cmd);
}