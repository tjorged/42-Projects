#include "pipex.h"

char	**paths_divider(char **envp)
{
	char	**paths;
	int		env_index;

	env_index = -1;
	while (envp[++env_index] != NULL)
	{
		if (ft_strncmp("PATH=", envp[env_index], 5) == 0)
		{
			paths = ft_split(envp[env_index], ':');
			if (!paths)
				exit(0);
			paths[0] = (paths[0] + 5);
			break;
		}
	}
	return (paths);
}

void add_slash(t_cmd *cmd, int argc)
{
	char	*temp;
	int		i;

	i = -1;
	while (++i <= argc - 4)
	{
		temp = ft_strdup(cmd[i].arg[0]);
		if (!temp)
			free_n_exit(cmd);
		free(cmd[i].arg[0]);
		cmd[i].arg[0] = ft_strjoin("/", temp);
		if (!cmd[i].arg[0])
			free_n_exit(cmd);
		free(temp);
	}
}

t_cmd	*command_allocation(int argc, char **argv)
{
	static t_cmd	*cmd;
	int		i;
	int		count;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * (argc - 3));
	i = 1;
	while (++i < argc - 1)
	{
		cmd[i - 2].arg = ft_split(argv[i], ' ');
		if (!cmd[i - 2].arg)
			free_n_exit(cmd);
	}
	add_slash(cmd, argc);
	cmd[0].process_nb =(argc - 3);
	return (cmd);
}

t_cmd	*check_command(int argc, char *argv[], char **paths)
{
	t_cmd	        *cmd;
	int				i;
	int				j;

	cmd = command_allocation(argc, argv);
	j = 1;
	while (++j < argc - 1)
	{
		i = 0;
		while (paths[i])
		{
			cmd[j - 2].path = ft_strjoin(paths[i], cmd[j - 2].arg[0]);
			if (!cmd[j - 2].path)
				free_n_exit(cmd);
			if (access(cmd[j - 2].path, X_OK) == 0)
				break ;
			else
				free(cmd[j - 2].path);
			i++;
			if (paths[i] == NULL)
				cmd[j - 2].path = ft_strdup(cmd[j - 2].arg[0] + 1);
		}
	}
	free_paths(paths);
	return (cmd);
}