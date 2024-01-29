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
		temp = ft_strdup(cmd[i + 1].arg[0]);
		if (!temp)
			free_n_exit(cmd);
		free(cmd[i + 1].arg[0]);
		cmd[i + 1].arg[0] = ft_strjoin("/", temp);
		if (!cmd[i + 1].arg[0])
			free_n_exit(cmd);
		free(temp);
	}
}

t_cmd	*command_allocation(int argc, char **argv)
{
	static t_cmd	*cmd;
	int		i;
	int		count;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * (argc - 2));
	if (!cmd)
	{
		perror(0);
		free_n_exit;
	}
	i = 1;
	while (++i < argc - 1)
	{
		cmd[i - 1].arg = ft_split(argv[i], ' ');
		if (!cmd[i - 1].arg)
			free_n_exit(cmd);
	}
	add_slash(cmd, argc);
	cmd[0].process_nb =(argc - 3);
	return (cmd);
}

void file_assigner(t_cmd *cmd, char **argv, int argc)
{
	cmd[0].arg = (char **)malloc(sizeof(char *) * 3);
	if (!cmd[0].arg)
		free_n_exit(cmd);
	cmd[0].arg[0] = ft_strdup(argv[1]);
	if (!cmd[0].arg[0])
		free_n_exit(cmd);
	cmd[0].arg[1] = ft_strdup(argv[argc - 1]);
	if (!cmd[0].arg[1])
		free_n_exit(cmd);
	cmd[0].arg[2] = NULL;
	cmd[0].fd[0] = open(cmd[0].arg[0], O_RDONLY);
	cmd[0].fd[1] = open(cmd[0].arg[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

t_cmd	*check_command(int argc, char **argv, char **paths)
{
	t_cmd	        *cmd;
	int				i;
	int				j;

	cmd = command_allocation(argc, argv);
	file_assigner(cmd, argv, argc);
	j = 1;
	while (++j < argc - 1)
	{
		i = 0;
		while (paths[i])
		{
			cmd[j - 1].path = ft_strjoin(paths[i], cmd[j - 1].arg[0]);
			if (!cmd[j - 1].path)
				free_n_exit(cmd);
			if (access(cmd[j - 1].path, X_OK) == 0)
				break ;
			else
				free(cmd[j - 1].path);
			i++;
			if (paths[i] == NULL)
				cmd[j - 1].path = ft_strdup(cmd[j - 1].arg[0] + 1);
		}
	}
	free_paths(paths);
	return (cmd);
}