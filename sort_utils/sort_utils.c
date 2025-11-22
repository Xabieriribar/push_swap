#include "../push_swap.h"

bool    last_is_biggest(t_list *list, t_list *last)
{
    while (list->next != NULL)
    {
        if (last->number < list->number)
            return (false);
        list = list->next;
    }
    return (true);
}

bool    swap_two(t_list **list)
{
    if ((*list)->number > (*list)->next->number)
    {
        sa(list, PRINT_IT);
        return (true);
    }
    return (false);
}

void    find_biggest_index(t_list *list, int *index)
{
    int max;
    t_list *max_node;

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

void    put_biggest_in_bottom(t_list **list)
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

void    sort_smallest(t_list **list_a)
{
    t_list *temp_a;
    t_list *smallest;

    temp_a = *list_a;
    while (temp_a != NULL)
    {
        smallest = find_smallest(*list_a);
        if (calculate_median(*list_a) > smallest->index)
        {
            while (smallest->index != 0)
            {
                ra(list_a, PRINT_IT);
                update_indexes(list_a, NULL);
            }
        }
        else
        {
            while (smallest->index != 0)
            {
                rra(list_a, PRINT_IT);
                update_indexes(list_a, NULL);
            }
        }
        temp_a = temp_a->next;
    }
}