/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_divider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:48:45 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:49:15 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	val_reducer(t_stack *a, t_stack *b)
{
	int	i;

	i = -1;
	while (++i <= a->max)
		a->stack[i] = (a->stack[i]) >> 1;
	i = -1;
	while (++i <= b->max)
		b->stack[i] = (b->stack[i]) >> 1;
}

static void	zeros_to_b(t_stack *a, t_stack *b)
{
	int	counter;

	counter = a->max + 1;
	while (counter > 0)
	{
		if ((a->stack[0]) & 1)
		{
			if (a->max > 0)
				rotate(a, 'a');
		}
		else
			push(a, b, 'b');
		counter--;
	}
}

static void	ones_to_a(t_stack *a, t_stack *b)
{
	int	counter;

	counter = b->max + 1;
	while (counter > 0)
	{
		if ((b->stack[0]) & 1)
			push(b, a, 'a');
		else
		{
			if (b->max > 0)
				rotate(b, 'b');
		}
		counter--;
	}
}

static int	divider_checker(t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	while (i <= a->max)
	{
		if (a->stack[i] != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i <= b->max)
	{
		if (b->stack[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

void	binary_divider(t_stack *a, t_stack *b)
{
	int	counter;

	zeros_to_b(a, b);
	val_reducer(a, b);
	while (!(divider_checker(a, b)))
	{
		zeros_to_b(a, b);
		ones_to_a(a, b);
		val_reducer(a, b);
	}
	counter = b->max + 1;
	while (counter > 0)
	{
		push(b, a, 'a');
		counter--;
	}
}
