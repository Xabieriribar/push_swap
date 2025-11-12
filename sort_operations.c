#include "push_swap.h"

void    sort_two(t_list_a **list, t_operations *operations)
{
    operations->index++;
    sa(list, operations);
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

bool    swap_two(t_list_a **list, t_operations *operations)
{
    if ((*list)->number > (*list)->next->number)
    {
        sa(list, operations);
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
void    put_biggest_in_bottom(t_list_a **list, t_operations *operation)
{
    int index;
    
    index = 0;
    find_biggest_index(*list, &index);
    if (index == 1)
    {
        rra(list, operation);
        operation->index++;
    }
    else
    {
        ra(list, operation);
        operation->index++;
        sa(list, operation);
        operation->index++;
    }

}
void    sort_three(t_list_a **list, t_operations *operations)
{
    t_list_a *last;

    last = ft_lstlast(*list);
    if (last_is_biggest(*list, last) && swap_two(list, operations))
        return ;
    else
    {
        put_biggest_in_bottom(list, operations);
        if (!ft_is_sorted(*list))
            sa(list, operations);
    }
}