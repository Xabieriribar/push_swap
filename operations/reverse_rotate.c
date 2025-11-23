/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   reverse_rotate.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:29:24 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:29:24 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Reverse Rotate A: The last element becomes the first one.
*/
void	rra(t_list **list, int mode)
{
	t_list	*node;
	t_list	*prev;

	node = *list;
	prev = ft_lstlast(*list);
	prev = prev->prev;
	*list = ft_lstlast(*list);
	node->prev = *list;
	(*list)->next = node;
	(*list)->prev = NULL;
	prev->next = NULL;
	if (mode == PRINT_IT)
		ft_printf("rra\n");
}

/*
** Reverse Rotate B: The last element becomes the first one.
*/
void	rrb(t_list **list, int mode)
{
	t_list	*node;
	t_list	*prev;

	node = *list;
	prev = ft_lstlast(*list);
	prev = prev->prev;
	*list = ft_lstlast(*list);
	node->prev = *list;
	(*list)->next = node;
	(*list)->prev = NULL;
	prev->next = NULL;
	if (mode == PRINT_IT)
		ft_printf("rrb\n");
}

/*
** Simultaneously reverse rotates both stack A and stack B.
*/
void	rrr(t_list **list_a, t_list **list_b)
{
	rra(list_a, 0);
	rrb(list_b, 0);
	ft_printf("rrr\n");
}
