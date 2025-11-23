/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   find_utils.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:16:57 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:17:02 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Traverses the provided list to find and return the node containing the
** highest integer value.
*/
t_list	*find_biggest(t_list *list)
{
	t_list	*biggest;

	biggest = list;
	while (list != NULL)
	{
		if (biggest->number < list->number)
			biggest = list;
		list = list->next;
	}
	return (biggest);
}

/*
** Traverses the provided list to find and return the node containing the
** lowest integer value.
*/
t_list	*find_smallest(t_list *list)
{
	t_list	*smallest;

	smallest = list;
	while (list != NULL)
	{
		if (smallest->number > list->number)
			smallest = list;
		list = list->next;
	}
	return (smallest);
}

/*
** Finds the "closest bigger" number in stack A 
** for a number coming from stack B.
** This is used to determine where a node from B 
** should land in A.
** If no bigger number exists, it returns the smallest node in A (cyclic order).
*/
t_list	*find_next_biggest(t_list *list_a, int source_number)
{
	t_list	*biggest;
	t_list	*smallest;
	t_list	*candidate;
	int		mode;

	biggest = find_biggest(list_a);
	smallest = find_smallest(list_a);
	if (source_number > biggest->number)
		return (smallest);
	mode = 0;
	candidate = list_a;
	while (list_a != NULL)
	{
		if (source_number < list_a->number
			&& (mode == 0 || candidate->number > list_a->number))
		{
			mode = 1;
			candidate = list_a;
		}
		list_a = list_a->next;
	}
	return (candidate);
}

/*
** Finds the "closest smaller" number in stack B for 
** a number coming from stack A.
** This is used to determine the target 
** position in B for a node being pushed from A.
** If no smaller number exists, it returns the biggest node in B (cyclic order).
*/
t_list	*find_next_smallest(t_list *list_b, int source_number)
{
	t_list	*biggest;
	t_list	*smallest;
	t_list	*candidate;
	int		mode;

	biggest = find_biggest(list_b);
	smallest = find_smallest(list_b);
	if (source_number < smallest->number)
		return (biggest);
	mode = 0;
	candidate = list_b;
	while (list_b != NULL)
	{
		if (source_number > list_b->number && (mode == 0
				|| list_b->number > candidate->number))
		{
			mode = 1;
			candidate = list_b;
		}
		list_b = list_b->next;
	}
	return (candidate);
}

/*
** Computes the middle index of the list. 
** This is used to decide whether it is
** more efficient to rotate up (RA/RB) 
** or reverse rotate down (RRA/RRB) to reach a node.
*/
int	calculate_median(t_list *list_a)
{
	int	median;

	median = 0;
	if (ft_lstsize(list_a) % 2 == 0)
	{
		median = ft_lstsize(list_a) / 2;
	}
	else
		median = (ft_lstsize(list_a) / 2) + 1;
	return (median);
}
