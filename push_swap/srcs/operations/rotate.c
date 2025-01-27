/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 06:34:29 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 07:36:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
// Rotates the top node of the stack to the bottom
static void	rotate(t_stack **stack)
{
	t_stack	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = find_last(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

// Rotates the top node of stack a to the bottom
void	ra(t_stack **stack_a)
{
	rotate(stack_a);
	ft_printf("ra\n");
}

// Rotates the top node of stack b to the bottom
void	rb(t_stack **stack_b)
{
	rotate(stack_b);
	ft_printf("rb\n");
}

// Rotates the top node of both stacks to the bottom
void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	ft_printf("rr\n");
}
