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

#include "push_swap.h"

void	ft_lstdelone(t_list_a *lst)
{
	if (!lst)
		return ;
	free(lst);
}
void	ft_lstclear(t_list_a **lst)
{
	t_list_a	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}
t_list_a *ft_lstnew(int number, int index, t_list_a *target_node)
{
	t_list_a *new;

	new = malloc(sizeof(struct s_list_a));
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

t_list_a *ft_lstlast(t_list_a *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void add_node(t_list_a **list, t_list_a *node)
{
	t_list_a *last;


	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	last = ft_lstlast(*list);
	last->next = node; 
	node->prev = last;
}

void    ft_fill_list(t_list_a **list, int *numbers, int argc)
{
	int index;
	t_list_a *node;

	index = 0;
	node = NULL;
	while (index < argc - 1)
	{
		node = ft_lstnew(numbers[index], index, NULL);
		add_node(list, node);
		index++;
	}
}

int ft_lstsize(t_list_a *list)
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

void    make_list(t_list_a **list, int *numbers, int argc)
{
	ft_fill_list(list, numbers, argc);
}

t_list_a *copy_list(t_list_a *list)
{
	t_list_a *new_list;
	t_list_a *new_node;

	new_list = NULL;
	while (list != NULL)
	{
		new_node = ft_lstnew(list->number, list->index, list->target_node);
		add_node(&new_list, new_node);
		list = list->next; 
	}
	return (new_list);
}
