/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   list_operations.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/22 08:48:49 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:24:26 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Frees all the memory allocated for the linked list nodes to prevent leaks
** when the program exits or encounters an error.
*/
void	stack_clear(t_stack **lst)
{
	t_stack	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

/*
** Allocates memory for a new node, initializes its value and index, and sets
** its pointers (next, prev, target) to NULL.
*/
t_stack	*stack_new(int number)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->index = 0;
	new->number = number;
	new->cost = 0;
	new->target_node = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/*
** Traverses the list to find and return the last node.
*/
t_stack	*stack_last(t_stack *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/*
** Converts the array of parsed integers into a doubly linked list structure,
** linking the `next` and `prev` pointers for each node.
*/
void	stack_fill(t_stack **list, int *numbers, int argc)
{
	int		index;
	t_stack	*node;
	t_stack	*last;

	index = 0;
	node = NULL;
	while (index < argc)
	{
		node = stack_new(numbers[index]);
		if (*list == NULL)
			*list = node;
		else
		{
			last = stack_last(*list);
			last->next = node;
			node->prev = last;
		}
		index++;
	}
}

/*
** Counts and returns the total number of nodes currently in the list.
*/
int	stack_size(t_stack *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
