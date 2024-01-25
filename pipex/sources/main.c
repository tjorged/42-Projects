#include "pipex.h"

void	forker(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd[0].process_nb)
	{
		pipe(cmd[i].fd);
		cmd[i].fork_id = fork();
		cmd[i].pipe_id = i;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	if (argc < 5)
		return (0);
	cmd = check_command(argc, argv, paths_divider(envp));
	ft_printf("%i\n", cmd[0].process_nb);
	free_cmd(cmd);
   // if (execve() == -1);
	return (0);
}