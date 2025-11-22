/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   push_swap.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/22 08:44:34 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/22 08:44:40 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    update_indexes(t_list **list_a, t_list **list_b)
{
    t_list *temp;
    int     index; 

    if (list_a != NULL)
    {
        index = 0;
        temp = *list_a;
        while (temp != NULL)
        {
            temp->index = index;
            index++;
            temp = temp->next;
        }
    }
    if (list_b == NULL)
        return ;
    temp = *list_b;
    index = 0;
    while (temp != NULL)
    {
        temp->index = index;
        index++;
        temp = temp->next;
    }
}
bool    ft_is_sorted(t_list *list)
{
    while (list->next != NULL)
    {
        if (list->number > list->next->number)
            return (false);
        list = list->next;
    }
    return (true);
}
void	initialise_data(int argc, char **argv, t_data *data)
{
	data->argc = argc;
	data->argv = argv;
	data->mode = 0;
}

void	free_data(t_data *data, int *nbr, t_list **list_a, t_list **list_b)
{
	free(data);
	free(nbr);
	ft_lstclear(list_a);
	ft_lstclear(list_b);
}

int	main(int argc, char **argv)
{
	int			*numbers;
	t_list	*list_a;
	t_list	*list_b;
	t_data		*data;

	list_a = NULL;
	list_b = NULL;
	data = malloc(sizeof(struct s_data));
	if (!data)
		return (0);
	initialise_data(argc, argv, data);
	if (!ft_parse_input(data, &numbers))
		return (write(2, "Error", 5), 0);
	ft_fill_list(&list_a, numbers, data->argc);
	if (!ft_is_sorted(list_a))
	{
		if (ft_lstsize(list_a) == 2)
			sort_two(&list_a);
		if (ft_lstsize(list_a) == 3)
			sort_three(&list_a);
		if (ft_lstsize(list_a) >= 4)
			sort_turks(&list_a, &list_b);
	}
	return (free_data(data, numbers, &list_a, &list_b), 0);
}
