#include "push_swap.h"

void    update_indexes(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp;
    int     index; 

    temp = *list_a;
    index = 0;
    while (temp != NULL)
    {
        temp->index = index;
        index++;
        temp = temp->next;
    }
    temp = *list_b;
    index = 0;
    while (temp != NULL)
    {
        temp->index = index;
        index++;
        temp = temp->next;
    }
}

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

t_list_a *find_closest_biggest(t_list_a *list, int biggest)
{
    t_list_a *closest_biggest;

    if (biggest != list->number)
        closest_biggest = list;
    else
        closest_biggest = list->next;
    while (list != NULL)
    {
        if (list->number > closest_biggest->number && list->number != biggest)
            closest_biggest = list;
        list = list->next;
    }
    return (closest_biggest);
}
t_list_a *find_next_biggest(t_list_a *list_a, int source_number)
{
    t_list_a *biggest;
    t_list_a *smallest;
    t_list_a *closest_biggest;

    biggest = find_biggest(list_a);
    smallest = find_smallest(list_a);
    if (source_number > biggest->number)
        return (smallest);
    while (true)
    {
        closest_biggest = find_closest_biggest(list_a, biggest->number);
        if (closest_biggest->number == biggest->number)
            return (closest_biggest);
        if (source_number > closest_biggest->number)
            return (biggest);
        if (closest_biggest->index == 0)
            return (closest_biggest);
        else
            biggest->number = closest_biggest->number;
    }
}
t_list_a *get_target_node(t_list_a *list_a, t_list_a *source_node, int to_find)
{
    t_list_a *target_node;
    int source_number;
    
    source_number = source_node->number;
    if (to_find == NEXT_BIGGEST)
    {
        target_node = list_a;
        return (find_next_biggest(list_a, source_number));
    }
    else
        return (0);
    return (target_node);
}