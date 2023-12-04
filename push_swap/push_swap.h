/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:13:16 by tjorge-d          #+#    #+#             */
/*   Updated: 2023/11/29 14:13:20 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>

typedef struct stack
{
	int	*stack;
	int	max;
}	t_stack;

void	r_rotate(t_stack *stack, char mode);
void	rotate(t_stack *stack, char mode);
void	push(t_stack *from, t_stack *to, char mode);
void	swap(t_stack *stack, char mode);
void	binary_divider(t_stack *a, t_stack *b);
void	push_swap(t_stack *a);

char	**arg_cleaner(char *args[], int ac);

int		arg_free(char **args, int size);
int		arg_counter(char **args);
int		*create_stack(char *numbers[], int size, int mode);

#endif
