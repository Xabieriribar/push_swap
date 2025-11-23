/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   target_utils.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:52:16 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:52:17 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Wrapper function that retrieves either the next biggest or next smallest node
** depending on the direction of the push (A to B or B to A).
*/
t_list	*get_target_node(t_list *list, t_list *source_node, int to_find)
{
	int	source_number;

	source_number = source_node->number;
	if (to_find == NEXT_BIGGEST)
		return (find_next_biggest(list, source_number));
	else if (to_find == NEXT_SMALLEST)
		return (find_next_smallest(list, source_number));
	return (0);
}

/*
** Checks where the target node is located (above or below median) and rotates
** the destination stack to bring the target to the top (index 0).
*/
void	is_target_below_or_above(t_list *target_node, t_list **list_a,
	t_list **list_b, int print)
{
	if (calculate_median(*list_a) >= target_node->index)
	{
		while (target_node->index != 0)
		{
			if (print == PRINT_IT)
				ra(list_a, PRINT_IT);
			update_indexes(list_a, NULL);
		}
		pa(list_a, list_b, PRINT_IT);
	}
	else
	{
		while (target_node->index != 0)
		{
			if (print == PRINT_IT)
				rra(list_a, PRINT_IT);
			update_indexes(list_a, list_b);
		}
		pa(list_a, list_b, PRINT_IT);
	}
}

/*
** Iterates through every node in stack A and finds its correct target position
** in stack B, storing the pointer to that target in the node structure.
*/
void	assign_target_nodes_to_a(t_list **list_a, t_list **list_b)
{
	t_list	*target_nodes;
	t_list	*temp_a;

	temp_a = *list_a;
	while (temp_a != NULL)
	{
		target_nodes = get_target_node(*list_b, temp_a, NEXT_SMALLEST);
		temp_a->target_node = target_nodes;
		temp_a = temp_a->next;
	}
}
