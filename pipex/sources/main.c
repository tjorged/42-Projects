#include "pipex.h"

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

void	pipes_closer(t_cmd *cmd, int current_proccess)
{
	int	i;

	i = -1;
	while (++i < cmd[0].process_nb)
	{
		close(cmd[i].fd[0]);
		close(cmd[i].fd[1]);
	}
}

void	forker(t_cmd *cmd, char **argv, char **envp)
{
	int	i;

	i = 0;
	ft_printf("process_nb = %i\n", cmd[0].process_nb);
	while (++i <= cmd[0].process_nb)
	{
		ft_printf("OI!\n");
		cmd[i].process_id = fork();
		if (cmd[i].process_id == -1)
			free_n_exit(cmd);
		if (cmd[i].process_id == 0)
		{
			ft_printf("%s\n", cmd[i].arg[0]);
			dup2(cmd[i - 1].fd[0], STDIN_FILENO);
			if (i == cmd[0].process_nb)
				dup2(cmd[0].fd[1] ,STDOUT_FILENO);
			else
				dup2(cmd[i].fd[1], STDOUT_FILENO);
			pipes_closer(cmd, i);
			if (access(cmd[i].path, X_OK) != 0)
			{
				Write(2, "Command, not found:", 20);
				Write(2, , 20);
			}
			execve(cmd[i].path, cmd[i].arg, envp);
			break;
		}
	}
	if (cmd[i].process_id != 0)
		pipes_closer(cmd, i);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		i = 0;

	if (argc < 5)
		return (0);
	file_name_checker(argc, argv, cmd);
	cmd = check_command(argc, argv, paths_divider(envp));
	file_name_checker(argc, argv, cmd);
	pipe_creator(cmd);
	forker(cmd, argv, envp);
	free_cmd(cmd);
	return (0);
}