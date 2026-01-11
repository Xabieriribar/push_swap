/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   from_a_to_b.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:34:54 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:36:42 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Executes the first phase of the algorithm: Pushes nodes from A to B until
** only three nodes remain in A. It always selects the node with the cheapest
** cost to push, ensuring the target in B is in the right position.
*/
void	from_a_to_b(t_stack **list_a, t_stack **list_b)
{
	int		mode;
	int		index_to_push_b;
	t_stack	*smallest_to_push;

	mode = 0;
	index_to_push_b = 0;
	while (stack_size(*list_a) > 3)
	{
		while (index_to_push_b < 2 || mode == 0)
		{
			pb(list_a, list_b, PRINT_IT);
			index_to_push_b++;
			mode = 1;
		}
		update_indexes(list_a, list_b);
		assign_target_nodes_to_a(list_a, list_b);
		update_indexes(list_a, list_b);
		smallest_to_push = find_cost(*list_a,
				stack_size(*list_a), stack_size(*list_b));
		update_indexes(list_a, list_b);
		push_to_top(smallest_to_push, list_a, list_b);
		pb(list_a, list_b, PRINT_IT);
	}
}
