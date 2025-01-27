

#include "push_swap.h"
//Identifies the node with the lowest push cost in the stack 
//and marks it as "cheapest"
void	set_cheapest(t_stack *stack)
{
	long		cheapest_value;
	t_stack		*cheapest_node;

	if (!stack)
		return ;
	cheapest_value = LONG_MAX;
	while (stack)
	{
		if (stack->cost < cheapest_value)
		{
			cheapest_value = stack->cost;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->cheapest = true;
}
// Assigns an index to each node in the stack and determines
//if it's above or below the median
void	current_index(t_stack *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++i;
	}
}

//Reverse rotates both stacks to move their respective target nodes to the top
void	rev_rotate_both(t_stack **a, t_stack **b, t_stack *cheapest_node)
{
	while (*b != cheapest_node->target && *a != cheapest_node)
		rrr(a, b);
	current_index(*a);
	current_index(*b);
}

//Rotates both stacks to move their respective target nodes to the top
void	rotate_both(t_stack **a, t_stack **b, t_stack *cheapest_node)
{
	while (*b != cheapest_node->target && *a != cheapest_node)
		rr(a, b);
	current_index(*a);
	current_index(*b);
}