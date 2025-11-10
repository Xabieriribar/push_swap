#include "push_swap.h"

bool    ft_is_sorted(t_list_a *list)
{
    while (list->next != NULL)
    {
        if (list->number > list->next->number)
            return (false);
        list = list->next;
    }
    return (true);
}

void    sa(t_list_a **list)
{
    int temp_number;
    int temp_index;

    temp_number = (*list)->number;
    temp_index = (*list)->index;
    (*list)->number = (*list)->next->number;
    (*list)->index = (*list)->next->index;
    (*list)->next->number = temp_number;
    (*list)->next->index = temp_index;
}