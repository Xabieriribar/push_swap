/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   sa.c                                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/23 08:32:32 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/23 08:32:33 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*This function adds element to the b stack, starting from the bottom
and adding them always at the top*/
void	sa(t_list **list, int mode)
{
	int	temp_number;
	int	temp_index;

	temp_number = 0;
	temp_index = 0;
	temp_number = (*list)->number;
	temp_index = (*list)->index;
	(*list)->number = (*list)->next->number;
	(*list)->index = (*list)->next->index;
	(*list)->next->number = temp_number;
	(*list)->next->index = temp_index;
	if (mode == PRINT_IT)
		ft_printf("sa\n");
}
