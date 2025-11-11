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

    temp_number = 0;
    temp_index = 0;
    temp_number = (*list)->number;
    temp_index = (*list)->index;
    (*list)->number = (*list)->next->number;
    (*list)->index = (*list)->next->index;
    (*list)->next->number = temp_number;
    (*list)->next->index = temp_index;
}

void    rra(t_list_a **list)
{
    t_list_a    *last;

    last = ft_lstlast(*list);
    last->prev->next = NULL;
    last->next = (*list)->next;
    last->prev = NULL;
    *list = last;
}

void    ra(t_list_a **list)
{
    t_list_a    *last;

    last = ft_lstlast(*list);
    last->next = (*list)->next;
    (*list)->prev = last->prev;
    last->prev->next = (*list);
    last->prev = NULL;
    (*list)->next = NULL;
}