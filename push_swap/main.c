/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:49:54 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:50:15 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	simplifier(int *sorted_stack, t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	while (i <= stack->max)
	{
		j = 0;
		while (stack->stack[j])
		{
			if (stack->stack[j] == sorted_stack[i])
			{
				stack->stack[j] = i + 1;
				break ;
			}
			j++;
		}
		i++;
	}
}

static int	*poor_sorter(int *stack, int size)
{
	int	temp;
	int	i;

	i = 1;
	if (stack == 0)
		return (0);
	while (i <= size)
	{
		if (stack[i] < stack[i - 1])
		{
			temp = stack[i];
			stack[i] = stack[i - 1];
			stack[i - 1] = temp;
			i = 1;
		}
		else
			i++;
	}
	return (stack);
}

static int	ints_checker(int *args, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= size)
	{
		j = i;
		while (++j <= size)
		{
			if (args[i] == args[j])
				return (1);
		}
	}
	return (0);
}

static int	error_handler(char **clean, t_stack *a, int *sorted, int mode)
{
	int	error;

	error = 0;
	if (mode == 1 && clean == NULL) 
		error = 1;
	if (mode == 2)
	{
		if (a->stack && ints_checker(a->stack, a->max))
		{
			free(a->stack);
			error = arg_free(clean, arg_counter(clean) - 1);
		}
		else if (a->stack == 0)
			error = arg_free(clean, arg_counter(clean) - 1);
	}
	else if (mode == 3 && sorted == 0)
	{
		free(a->stack);
		error = arg_free(clean, arg_counter(clean) - 1);
	}
	if (error)
		write(1, "Error\n", 6);
	return (error);
}

int	main(int argc, char *argv[])
{
	t_stack	a;
	char	**clean_args;
	int		*sorted_stack;

	if (argc == 1)
		return (0);
	clean_args = arg_cleaner(argv, argc);
	if (error_handler(clean_args, &a, NULL, 1))
		return (0);
	a.max = arg_counter(clean_args) - 1;
	a.stack = create_stack(clean_args, a.max + 2, 'a');
	if (error_handler(clean_args, &a, NULL, 2))
		return (0);
	sorted_stack = poor_sorter(create_stack(clean_args, a.max + 2, 'a'), a.max);
	if (error_handler(clean_args, &a, sorted_stack, 3))
		return (0);
	simplifier(sorted_stack, &a);
	push_swap(&a);
	arg_free(clean_args, a.max);
	free(sorted_stack);
	free(a.stack);
}
