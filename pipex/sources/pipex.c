/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:29:40 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/01/30 16:29:45 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipes_closer(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd[0].process_nb)
	{
		if (cmd[i].fd[0])
			close(cmd[i].fd[0]);
		if (cmd[i].fd[1])
			close(cmd[i].fd[1]);
	}
}

int	here_docker(t_cmd *cmd)
{
	char	*str;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		str = get_next_line(0);
		if (!str)
			free_n_exit(cmd);
		if (ft_strncmp(cmd[0].arg[0], str, ft_strlen(cmd[0].arg[0])) == 0 \
		&& ft_strlen(cmd[0].arg[0]) == (ft_strlen(str) - 1))
			break ;
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
	free(str);
	close(fd[1]);
	return (fd[0]);
}

void	pipe_creator(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (++i < cmd[0].process_nb)
	{
		if (pipe(cmd[i].fd) == -1)
			free_n_exit(cmd);
	}
}

static void	proccess_cmd(t_cmd *cmd, char **envp, int i)
{
	dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	if (i == cmd[0].process_nb)
		dup2(cmd[0].fd[1], STDOUT_FILENO);
	else
		dup2(cmd[i].fd[1], STDOUT_FILENO);
	pipes_closer(cmd);
	execve(cmd[i].path, cmd[i].arg, envp);
}

void	forker(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (++i <= cmd[0].process_nb)
	{
		cmd[i].process_id = fork();
		if (cmd[i].process_id == -1)
			free_n_exit(cmd);
		if (cmd[i].process_id == 0)
		{
			if (access(cmd[i].path, X_OK) != 0)
				error_msg(cmd[i].arg[0], 1);
			else
				proccess_cmd(cmd, envp, i);
			break ;
		}
	}
	pipes_closer(cmd);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
}
