/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   sort_operations.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:46:59 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:47:00 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Simple swap to sort two elements.
*/
void	sort_two(t_list **list)
{
	sa(list, PRINT_IT);
}

/*
** Sorts three elements using the minimal number of moves (max 2 operations).
** Checks specific permutations to decide whether to swap or rotate.
*/
void	sort_three(t_list **list)
{
	t_list	*last;

	last = ft_lstlast(*list);
	if (last_is_biggest(*list, last) && swap_two(list))
		return ;
	else
	{
		put_biggest_in_bottom(list);
		if (!ft_is_sorted(*list))
			sa(list, PRINT_IT);
	}
}

/*
** The main algorithm function ("Turk Algo").
** 1. Push A to B (leaving 3).
** 2. Sort the 3 remaining in A.
** 3. Push B back to A.
** 4. Final rotation to ensure the smallest number is at the start.
*/
void	sort_turks(t_list **list_a, t_list **list_b)
{
	if (ft_lstsize(*list_a) > 5)
		from_a_to_b(list_a, list_b);
	while (ft_lstsize(*list_a) > 3)
		pb (list_a, list_b, PRINT_IT);
	update_indexes(list_a, list_b);
	if (!ft_is_sorted(*list_a))
		sort_three(list_a);
	update_indexes(list_a, list_b);
	from_b_to_a(list_a, list_b);
	sort_smallest(list_a);
	update_indexes(list_a, list_b);
}
