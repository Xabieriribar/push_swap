/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   sort_utils.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:48:46 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:48:47 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Helper check for sort_three logic: 
** checks if the last node is the largest value.
*/
bool	last_is_biggest(t_stack *list, t_stack *last)
{
	while (list->next != NULL)
	{
		if (last->number < list->number)
			return (false);
		list = list->next;
	}
	return (true);
}

/*
** Checks if the first two elements are unordered and swaps them if necessary.
*/
bool	swap_two(t_stack **list)
{
	if ((*list)->number > (*list)->next->number)
	{
		sa(list, PRINT_IT);
		return (true);
	}
	return (false);
}

/*
** Locates the index (position) of the largest number in the list.
*/
void	find_biggest_index(t_stack *list, int *index)
{
	int		max;
	t_stack	*max_node;

	max = list->number;
	max_node = NULL;
	while (list->next != NULL)
	{
		if (list->next->number > max)
		{
			max = list->next->number;
			max_node = list->next;
			*index = max_node->index;
		}
		list = list->next;
	}
}

/*
** Rotates the list to place the largest number at the bottom, which simplifies
** the sorting of the remaining two top elements.
*/
void	put_biggest_in_bottom(t_stack **list)
{
	int	index;

	index = 0;
	find_biggest_index(*list, &index);
	if (index == 1)
	{
		rra(list, PRINT_IT);
	}
	else
	{
		ra(list, PRINT_IT);
		if (!ft_is_sorted(*list))
			sa(list, PRINT_IT);
	}
}

/*
** Final adjustment step: Rotates stack A until the smallest number is at the
** head of the list, ensuring the stack is perfectly sorted (e.g., 1 2 3 4 5).
*/
void	sort_smallest(t_stack **list_a)
{
	t_stack	*smallest;

	smallest = find_smallest(*list_a);
	if (calculate_median(*list_a) > smallest->index)
	{
		while (smallest->index != 0)
		{
			ra(list_a, PRINT_IT);
			update_indexes(list_a, NULL);
		}
	}
	else
	{
		while (smallest->index != 0)
		{
			rra(list_a, PRINT_IT);
			update_indexes(list_a, NULL);
		}
	}
}
