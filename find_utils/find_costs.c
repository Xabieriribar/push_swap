/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   find_costs.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:05:50 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:05:52 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
/*
** Calculates the cost of moving a node to the top of stack A and its target
** to the top of stack B. It evaluates four scenarios: both moving up, both
** moving down, and the two mixed cases, returning the minimum cost found.
*/
int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	set_costs(int index_a, int index_target, int len_a, int len_b)
{
	int	cost_1;
	int	cost_2;
	int	cost_3;
	int	cost_4;

	cost_1 = ft_max(index_a, index_target);
	cost_2 = ft_max(len_a - index_a, len_b - index_target);
	cost_3 = index_a + (len_b - index_target);
	cost_4 = (len_a - index_a) + index_target;
	return (ft_min(ft_min(cost_1, cost_2), ft_min(cost_3, cost_4)));
}

/*
** Iterates through the list to find the node with the absolute lowest move cost.
** If two nodes have the same cost, it prioritizes the one with the lower index
** (closer to the top) to ensure stability.
*/
t_list	*return_lowest_cost_node(t_list *list_a)
{
	t_list	*lowest_cost_node;

	lowest_cost_node = list_a;
	while (list_a != NULL)
	{
		if (list_a->cost < lowest_cost_node->cost)
			lowest_cost_node = list_a;
		else if (list_a->cost == lowest_cost_node->cost
			&& list_a->index < lowest_cost_node->index)
			lowest_cost_node = list_a;
		list_a = list_a->next;
	}
	return (lowest_cost_node);
}

/*
** Main driver for cost calculation. It assigns a cost to every node in stack A
** based on its current position and the position of its target in stack B,
** then returns the node that is cheapest to move.
*/
t_list	*find_cost(t_list *list_a, int len_a, int len_b)
{
	t_list	*target_b;
	t_list	*head_list;

	head_list = list_a;
	while (list_a != NULL)
	{
		target_b = list_a->target_node;
		list_a->cost = set_costs(list_a->index, target_b->index, len_a, len_b);
		list_a = list_a->next;
	}
	return (return_lowest_cost_node(head_list));
}
