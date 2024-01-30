/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:30:13 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/30 16:30:15 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd	*command_allocation(int argc, char **argv)
{
	static t_cmd	*cmd;
	int				i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * (argc - 2));
	if (!cmd)
	{
		perror(0);
		exit(0);
	}
	i = 1;
	while (++i < argc - 1)
	{
		cmd[i - 1].arg = ft_split(argv[i], ' ');
		if (!cmd[i - 1].arg)
			free_n_exit(cmd);
	}
	cmd[0].process_nb = (argc - 3);
	return (cmd);
}

static void	file_assigner(t_cmd *cmd, char **argv, int argc, int here_doc)
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
	if (!here_doc)
	{
		cmd[0].fd[0] = open(cmd[0].arg[0], O_RDONLY);
		cmd[0].fd[1] = open(cmd[0].arg[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		cmd[0].fd[0] = here_docker(cmd);
		cmd[0].fd[1] = open(cmd[0].arg[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	path_joiner(t_cmd *cmd, char **paths, int i, int j)
{
	char	*temp;

	temp = ft_strjoin(paths[i], "/");
	if (!temp)
	{
		free_paths(paths);
		free_n_exit(cmd);
	}
	cmd[j - 1].path = ft_strjoin(temp, cmd[j - 1].arg[0]);
	if (!cmd[j - 1].path)
	{
		free_paths(paths);
		free_n_exit(cmd);
	}
	free(temp);
}

t_cmd	*check_command(int argc, char **argv, char **paths, int here_doc)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = command_allocation(argc, argv);
	file_assigner(cmd, argv, argc, here_doc);
	j = 1;
	while (++j < argc - 1)
	{
		i = 0;
		while (paths[i])
		{
			path_joiner(cmd, paths, i, j);
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
