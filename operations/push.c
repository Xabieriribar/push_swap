/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   push.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:26:35 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:26:41 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Pushes the top element of stack A to the top of stack B.
*/
void	pb(t_list **list_a, t_list **list_b, int mode)
{
	t_list	*temp;

	if (!*list_a)
		return ;
	temp = *list_a;
	*list_a = (*list_a)->next;
	if (*list_a)
		(*list_a)->prev = NULL;
	temp->next = *list_b;
	if (*list_b)
		(*list_b)->prev = temp;
	*list_b = temp;
	if (mode == PRINT_IT)
		ft_printf("pb\n");
}

/*
** Pushes the top element of stack B to the top of stack A.
*/
void	pa(t_list **list_a, t_list **list_b, int mode)
{
	t_list	*temp;

	if (!*list_b)
		return ;
	temp = *list_b;
	*list_b = (*list_b)->next;
	if (*list_b)
		(*list_b)->prev = NULL;
	temp->next = *list_a;
	if (*list_a)
		(*list_a)->prev = temp;
	*list_a = temp;
	if (mode == PRINT_IT)
		ft_printf("pa\n");
}
