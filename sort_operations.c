#include "push_swap.h"

void    sort_two(t_list_a **list)
{
    sa(list);
}

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
        sa(list);
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
        rra(list);
    }
    else
    {
        ra(list);
        sa(list);
    }

}
void    sort_three(t_list_a **list)
{
    t_list_a *last;

    last = ft_lstlast(*list);
    if (last_is_biggest(*list, last) && swap_two(list))
        return ;
    else
    {
        put_biggest_in_bottom(list);
        if (!ft_is_sorted(*list))
            sa(list);
    }
}
