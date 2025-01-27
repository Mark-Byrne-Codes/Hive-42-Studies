/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_error_handlers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:42:02 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 07:30:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Validates if the string represents a valid number
int	is_valid_numbers(char *str)
{
	if (!str || (!ft_isdigit(*str) && *str != '+' && *str != '-'))
		return (1);
	if ((*str == '+' || *str == '-') && !ft_isdigit(*(str + 1)))
		return (1);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

// Checks for duplicate numbers in the stack
int	has_error_dup(t_stack *stack_a, int n)
{
	if (!stack_a)
		return (0);
	while (stack_a)
	{
		if (stack_a->nbr == n)
			return (1);
		stack_a = stack_a->next;
	}
	return (0);
}

// Frees all nodes in the stack and sets the stack pointer to NULL
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		current->nbr = 0;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

// Frees the stack and prints an error message
void	free_errors(t_stack **stack_a)
{
	free_stack(stack_a);
	ft_printf("Error\n");
	exit(1);
}

// Frees the split strings
void	free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
