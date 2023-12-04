/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:51:51 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:51:53 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	ft_atoi(const char *nb, int *error, long n, long v)
{
	unsigned int	i;

	i = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			v = -v;
		i++;
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			(*error) = 1;
	}
	while (nb[i] == '0' && nb[i + 1] != '0')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9' && n < 2147483649)
	{
		n = (n * 10) + (nb[i] - 48);
		i++;
	}
	if ((n * v) > 2147483647 || (n * v) < -2147483648)
		(*error) = 1;
	return (n * v);
}

int	*create_stack(char *numbers[], int size, int mode)
{
	int	error;
	int	*stack;
	int	i;

	error = 0;
	stack = (int *)malloc(sizeof(int) * size);
	if (!stack)
		return (0);
	while (--size >= 0)
		stack[size] = 0;
	if (mode == 'a')
	{
		i = -1;
		while (numbers[++i])
		{
			stack[i] = ft_atoi(numbers[i], &error, 0, 1);
			if (error)
			{
				free(stack);
				return (0);
			}
		}
	}
	return (stack);
}

int	arg_counter(char **args)
{
	int	n;

	n = 0;
	while (args[n])
		n++;
	return (n);
}

int	arg_free(char **args, int size)
{
	int	i;

	i = size;
	while (i >= 0)
		free(args[i--]);
	free(args);
	return (1);
}
