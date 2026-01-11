/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   from_b_to_a.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:37:00 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:37:01 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Executes the final phase: Pushes everything back from B to A. It ensures
** the correct target position in A is at the top before pushing, maintaining
** the sorted order.
*/
void	from_b_to_a(t_stack **list_a, t_stack **list_b)
{
	t_stack	*target_node;

	while (stack_size(*list_b) > 0)
	{
		target_node = get_target_node(*list_a, *list_b, NEXT_BIGGEST);
		if (target_node->index == 0)
		{
			pa(list_a, list_b, PRINT_IT);
			update_indexes(list_a, list_b);
		}
		else
			is_target_below_or_above(target_node,
				list_a, list_b, PRINT_IT);
		update_indexes(list_a, list_b);
	}
}
