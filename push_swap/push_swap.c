/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:51:40 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:51:43 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	thirds(t_stack *a)
{
	if (a->stack[0] == 3)
	{
		rotate(a, 'a');
		if (a->stack[0] == 2)
			swap(a, 'a');
	}
	else if (a->stack[0] == 2 && a->stack[2] == 1)
		r_rotate(a, 'a');
	else if (a->stack[0] == 2 && a->stack[2] == 3)
		swap(a, 'a');
	else if (a->stack[0] == 1 && a->stack[1] == 3)
	{
		swap(a, 'a');
		rotate(a, 'a');
	}
}

static void	fourths_n_fifths(t_stack *a, t_stack *b, char mode)
{
	while (mode == '4' && b->max != 0)
	{
		if (a->stack[0] == 4)
			push(a, b, 'b');
		else
			rotate(a, 'a');
	}
	while (mode == '5' && b->max != 1)
	{
		if (a->stack[0] == 4 || a->stack[0] == 5)
			push(a, b, 'b');
		else
			rotate(a, 'a');
	}
	thirds(a);
	if (b->stack[0] == 5)
		swap(b, 'b');
	push(b, a, 'a');
	rotate(a, 'a');
	if (mode == '5')
	{
		push(b, a, 'a');
		rotate(a, 'a');
	}
}

static int	sort_check(t_stack *a)
{
	int	i;

	i = 0;
	while (++i <= a->max)
	{
		if (a->stack[i] < a->stack[i - 1])
			return (0);
	}
	return (1);
}

void	push_swap(t_stack *a)
{
	t_stack	b;

	if (a->max == 1 && a->stack[0] != 1)
		swap(a, 'a');
	else if (a->max == 2 && !(a->stack[0] == 1 && a->stack[1] == 2))
		thirds(a);
	if (sort_check(a))
		return ;
	b.max = -1;
	b.stack = create_stack(NULL, a->max + 2, 'b');
	if (a->max == 3)
		fourths_n_fifths(a, &b, '4');
	else if (a->max == 4)
		fourths_n_fifths(a, &b, '5');
	else
		binary_divider(a, &b);
	free(b.stack);
}
