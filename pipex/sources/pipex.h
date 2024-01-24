#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_cmd
{
	char    *path;
    char    **arg;
    int     infd;
    int     outfd;
    int     accessible;
	int		process_nb;
}	t_cmd;

#endif

