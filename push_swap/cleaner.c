/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:49:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:49:46 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	arg_count(char *args[])
{
	int	arg_nb;
	int	j;
	int	i;

	arg_nb = 0;
	j = 0;
	while (args[++j])
	{
		i = 0;
		while (args[j][i])
		{
			while (args[j][i] == ' ')
				i++;
			if (args[j][i])
				arg_nb++;
			while (args[j][i] != ' ' && args[j][i])
				i++;
		}
	}
	return (arg_nb);
}

static int	arg_error(char *args[], char *curr_arg, int prev_arg, int mode)
{
	int	i[2];

	i[1] = 0;
	while (mode == 1 && args[++i[1]])
	{
		i[0] = 0;
		while (args[i[1]][i[0]])
		{
			while (args[i[1]][i[0]] == ' ')
				i[0]++;
			while (args[i[1]][i[0]] != ' ' && args[i[1]][i[0]])
			{
				if (!(args[i[1]][i[0]] >= '0' && args[i[1]][i[0]] <= '9') 
				&& !(args[i[1]][i[0]] == '-' || args[i[1]][i[0]] == '+'))
					return (arg_free(args, -1));
				if ((args[i[1]][i[0]] >= '0' && args[i[1]][i[0]] <= '9') 
				&& (args[i[1]][i[0] + 1] == '-' || args[i[1]][i[0] + 1] == '+'))
					return (arg_free(args, -1));
				i[0]++;
			}
		}
	}
	if (mode == 2 && !curr_arg)
		return (arg_free(args, prev_arg - 2));
	return (0);
}

static void	arg_alloc(char *args[], char *new_args[], int nj, int ni)
{
	int	i[2];

	i[1] = 0;
	while (args[++i[1]])
	{
		i[0] = 0;
		while (args[i[1]][i[0]])
		{
			ni = 0;
			while (args[i[1]][i[0]] == ' ')
				i[0]++;
			while (args[i[1]][i[0]] != ' ' && args[i[1]][i[0]])
			{
				ni++;
				i[0]++;
			}
			if (ni > 0)
			{
				new_args[nj++] = (char *)malloc(sizeof(char) * ni + 1);
				if (arg_error(new_args, new_args[nj - 1], nj - 2, 2))
					return ;
				new_args[nj - 1][ni] = '\0';
			}
		}
	}
}

static void	arg_separator(char *args[], char *new_args[], int nj, int ni)
{
	int	j;
	int	i;

	j = 0;
	while (args[++j])
	{
		i = 0;
		while (args[j][i])
		{
			ni = 0;
			while (args[j][i] == ' ')
				i++;
			if (args[j][i])
				nj++;
			while (args[j][i] != ' ' && args[j][i])
			{
				new_args[nj][ni] = args[j][i];
				ni++;
				i++;
			}
		}
	}
}

char	**arg_cleaner(char *args[], int ac)
{
	char	**new_args;
	char	**temp;
	int		n;

	n = -1;
	temp = (char **)malloc(sizeof(char *) * (ac + 1));
	if (!temp)
		return (NULL);
	while (++n < ac)
		temp[n] = args[n];
	temp[ac] = NULL;
	if (arg_error(temp, NULL, ac, 1))
		return (NULL);
	n = arg_count(temp);
	new_args = (char **)malloc(sizeof(char *) * (n + 1));
	if (!new_args)
		return (NULL);
	new_args[n] = NULL;
	arg_alloc(temp, new_args, 0, 0);
	if (!new_args)
		return (NULL);
	arg_separator(temp, new_args, -1, 0);
	free(temp);
	return (new_args);
}
