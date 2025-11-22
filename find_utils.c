#include "push_swap.h"

t_list_a *find_biggest(t_list_a *list)
{
    t_list_a *biggest;
    biggest = list;
    while (list != NULL)
    {
        if (biggest->number < list->number)
            biggest = list;
        list = list->next;
    }
    return (biggest);

}

t_list_a *find_smallest(t_list_a *list)
{
    t_list_a *smallest;
    smallest = list;
    while (list != NULL)
    {
        if (smallest->number > list->number)
            smallest = list;
        list = list->next;
    }
    return (smallest);

}

t_list_a *find_next_biggest(t_list_a *list_a, int source_number)
{
    t_list_a *biggest;
    t_list_a *smallest;
    t_list_a *candidate;
    int mode;

    biggest = find_biggest(list_a);
    smallest = find_smallest(list_a);
    if (source_number > biggest->number)
        return (smallest);
    mode = 0;
    candidate = list_a;
    while (list_a != NULL)
    {
        if (source_number < list_a->number && (mode == 0 || candidate->number > list_a->number))
        {
            mode = 1;
            candidate = list_a;
        }
        list_a = list_a->next;
    }
    return (candidate);
}

t_list_a *find_next_smallest(t_list_a *list_b, int source_number)
{
    t_list_a *biggest;
    t_list_a *smallest;
    t_list_a *candidate;
    int      mode;

    biggest = find_biggest(list_b);
    smallest = find_smallest(list_b);
    if (source_number < smallest->number)
        return (biggest);
    mode = 0;
    candidate = list_b;
    while (list_b != NULL)
    {
        if (source_number > list_b->number && (mode == 0 || list_b->number > candidate->number))
        {
            mode = 1;
            candidate = list_b;
        }
        list_b = list_b->next;
    }
    return (candidate);
}
t_list_a *find_cost(t_list_a *list_a, int len_a, int len_b)
{
    t_list_a *target_b;
    t_list_a *head_list;

    head_list = list_a;
    while (list_a != NULL)
    {
        target_b = list_a->target_node;
        list_a->cost = set_costs(list_a->index, target_b->index, len_a, len_b);
        list_a = list_a->next;
    }
    return (return_lowest_cost_node(head_list));
}