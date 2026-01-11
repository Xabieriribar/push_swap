/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   push_to_top.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:38:37 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:38:37 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Optimizes movement when both the source node and target node are in the
** bottom half of their stacks. Uses 'rrr' to rotate both simultaneously,
** then finishes with individual rotations.
*/
void	loop_if_below_median(t_stack *smallest_to_push, t_stack *target_node,
	t_stack **list_a, t_stack **list_b)
{
	while (smallest_to_push->index != 0 && target_node->index != 0)
	{
		rrr(list_a, list_b);
		update_indexes(list_a, list_b);
	}
	while (smallest_to_push->index != 0)
	{
		rra(list_a, PRINT_IT);
		update_indexes(list_a, list_b);
	}
	while (target_node->index != 0)
	{
		rrb(list_b, PRINT_IT);
		update_indexes(list_a, list_b);
	}
}

/*
** Handles the case where the source is in the bottom half (needs RRA)
** but the target is in the top half (needs RB). 
** No simultaneous optimization possible.
*/
void	high_cost_loop_one(t_stack *smallest_to_push, t_stack *target_node,
	t_stack **list_a, t_stack **list_b)
{
	while (smallest_to_push->index != 0)
	{
		rra(list_a, PRINT_IT);
		update_indexes(list_a, list_b);
	}
	while (target_node->index != 0)
	{
		rb(list_b, PRINT_IT);
		update_indexes(list_a, list_b);
	}
}

/*
** Optimizes movement when both the source node and target node are in the
** top half of their stacks. Uses 'rr' to rotate both simultaneously,
** then finishes with individual rotations.
*/
void	loop_if_above_median(t_stack *smallest_to_push, t_stack *target_node,
	t_stack **list_a, t_stack **list_b)
{
	while (smallest_to_push->index != 0 && target_node->index != 0)
	{
		rr(list_a, list_b);
		update_indexes(list_a, list_b);
	}
	while (smallest_to_push->index != 0)
	{
		ra(list_a, PRINT_IT);
		update_indexes(list_a, list_b);
	}
	while (target_node->index != 0)
	{
		rb(list_b, PRINT_IT);
		update_indexes(list_a, list_b);
	}
}

/*
** Handles the case where the source is in the top half (needs RA)
** but the target is in the bottom half (needs RRB). 
** No simultaneous optimization possible.
*/
void	high_cost_loop_two(t_stack *smallest_to_push, t_stack *target_node,
	t_stack **list_a, t_stack **list_b)
{
	while (smallest_to_push->index != 0)
	{
		ra(list_a, PRINT_IT);
		update_indexes(list_a, list_b);
	}
	while (target_node->index != 0)
	{
		rrb(list_b, PRINT_IT);
		update_indexes(list_a, list_b);
	}
}

/*
** Orchestrates the physical movement of nodes. It checks the position of the
** node and its target relative to the median to select the most efficient
** rotation strategy (rr, rrr, or mixed) before pushing.
*/
void	push_to_top(t_stack *smallest_to_push,
	t_stack **list_a, t_stack **list_b)
{
	if (calculate_median(*list_a) >= smallest_to_push->index
		&& calculate_median(*list_b) >= smallest_to_push->target_node->index)
		loop_if_above_median(smallest_to_push,
			smallest_to_push->target_node, list_a, list_b);
	else if (calculate_median(*list_a) < smallest_to_push->index
		&& calculate_median(*list_b) < smallest_to_push->target_node->index)
		loop_if_below_median(smallest_to_push,
			smallest_to_push->target_node, list_a, list_b);
	else
	{
		if (calculate_median(*list_a) < smallest_to_push->index
			&& calculate_median(*list_b)
			>= smallest_to_push->target_node->index)
			high_cost_loop_one(smallest_to_push,
				smallest_to_push->target_node, list_a, list_b);
		else if (calculate_median(*list_a) >= smallest_to_push->index
			&& calculate_median(*list_b) < smallest_to_push->target_node->index)
			high_cost_loop_two(smallest_to_push,
				smallest_to_push->target_node, list_a, list_b);
	}
}
