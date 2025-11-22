/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   list_operations.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/22 08:48:49 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/22 08:48:50 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}
t_list *ft_lstnew(int number, int index, t_list *target_node)
{
	t_list *new;

	new = malloc(sizeof(struct s_list));
	if (!new)
		return (NULL);
	new->index = index;
	new->number = number;
	if (target_node != NULL)
		new->target_node = target_node;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_list *ft_lstlast(t_list *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void    ft_fill_list(t_list **list, int *numbers, int argc)
{
	int index;
	t_list *node;
	t_list *last;

	index = 0;
	node = NULL;
	while (index < argc - 1)
	{
		node = ft_lstnew(numbers[index], index, NULL);
		if (*list == NULL)
			*list = node;
		else
		{
			last = ft_lstlast(*list);
			last->next = node; 
			node->prev = last;
		}
		index++;
	}
}

int ft_lstsize(t_list *list)
{
	int len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
