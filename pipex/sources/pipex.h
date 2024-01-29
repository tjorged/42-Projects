#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_cmd
{
	char    *path;
    char    **arg;
    int     fd[2];
    int     pipe_id;
    int     process_id;
	int		process_nb;
}   t_cmd;

//parser.c
char	**paths_divider(char **envp);
void    add_slash(t_cmd *cmd, int argc);
void    file_assigner(t_cmd *cmd, char **argv, int argc);
t_cmd	*command_allocation(int argc, char **argv);
t_cmd	*check_command(int argc, char *argv[], char **paths);

//pipex_utils.c
void    free_n_exit(t_cmd *cmd);
void    free_paths(char **paths);
void	free_cmd(t_cmd *cmd);

//file_names.c
void	file_name_checker(int argc, char **argv, t_cmd *cmd);

#endif

