/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   rotate.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:31:01 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:31:01 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Rotate A: The first element becomes the last one.
*/
void	ra(t_list **list, int mode)
{
	t_list	*first_temp;
	t_list	*last_temp;

	first_temp = (*list);
	last_temp = ft_lstlast(*list);
	*list = (*list)->next;
	last_temp->next = first_temp;
	first_temp->prev = last_temp;
	first_temp->next = NULL;
	if (mode == PRINT_IT)
		ft_printf("ra\n");
}

/*
** Rotate B: The first element becomes the last one.
*/
void	rb(t_list **list, int mode)
{
	t_list	*first_temp;
	t_list	*last_temp;

	first_temp = (*list);
	last_temp = ft_lstlast(*list);
	*list = (*list)->next;
	last_temp->next = first_temp;
	first_temp->prev = last_temp;
	first_temp->next = NULL;
	if (mode == PRINT_IT)
		ft_printf("rb\n");
}

/*
** Simultaneously rotates both stack A and stack B.
*/
void	rr(t_list **list_a, t_list **list_b)
{
	ra(list_a, 0);
	rb(list_b, 0);
	ft_printf("rr\n");
}
