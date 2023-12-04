/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:50:34 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 13:51:23 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	r_rotate(t_stack *stack, char mode)
{
	int	temp;
	int	i;

	temp = stack->stack[stack->max];
	i = stack->max + 1;
	while (--i > 0)
		stack->stack[i] = stack->stack[i - 1];
	stack->stack[0] = temp;
	if (mode == 'a')
		write(1, "rra\n", 4);
	if (mode == 'b')
		write(1, "rrb\n", 4);
}

void	rotate(t_stack *stack, char mode)
{
	int	temp;
	int	i;

	i = -1;
	temp = stack->stack[0];
	while (++i < stack->max)
		stack->stack[i] = stack->stack[i + 1];
	stack->stack[stack->max] = temp;
	if (mode == 'a')
		write(1, "ra\n", 3);
	if (mode == 'b')
		write(1, "rb\n", 3);
}

void	push(t_stack *from, t_stack *to, char mode)
{
	int	i;

	i = to->max + 1;
	while (--i >= 0)
		to->stack[i + 1] = to->stack[i];
	to->max++;
	to->stack[0] = from->stack[0];
	while (++i <= from->max)
		from->stack[i] = from->stack[i + 1];
	from->max--;
	if (mode == 'a')
		write(1, "pa\n", 3);
	if (mode == 'b')
		write(1, "pb\n", 3);
}

void	swap(t_stack *stack, char mode)
{
	int	temp;

	temp = stack->stack[0];
	stack->stack[0] = stack->stack[1];
	stack->stack[1] = temp;
	if (mode == 'a')
		write(1, "sa\n", 3);
	if (mode == 'b')
		write(1, "sb\n", 3);
}
