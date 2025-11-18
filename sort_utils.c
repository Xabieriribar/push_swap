#include "push_swap.h"

bool    last_is_biggest(t_list_a *list, t_list_a *last)
{
    while (list->next != NULL)
    {
        if (last->number < list->number)
            return (false);
        list = list->next;
    }
    return (true);
}

bool    swap_two(t_list_a **list)
{
    if ((*list)->number > (*list)->next->number)
    {
        sa(list, PRINT_IT);
        return (true);
    }
    return (false);
}

void    find_biggest_index(t_list_a *list, int *index)
{
    int max;
    t_list_a *max_node;

    max = list->number;
    max_node = NULL;
    while (list->next != NULL)
    {
        if (list->next->number > max)
        {
            max = list->next->number;
            max_node = list->next;
            *index = max_node->index;
        }
        list = list->next;
    }
}

void    put_biggest_in_bottom(t_list_a **list)
{
    int index;

    index = 0;
    find_biggest_index(*list, &index);
    if (index == 1)
    {
        rra(list, PRINT_IT);
    }
    else
    {
        ra(list, PRINT_IT);
        if (!ft_is_sorted(*list))
            sa(list, PRINT_IT);
    }

}