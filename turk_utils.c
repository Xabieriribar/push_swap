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
    if (!ft_is_sorted(list_a))
    {

    }
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
t_list_a *get_target_node(t_list_a *list_a, t_list_a *source_node, int to_find)
{
    int source_number;
    
    source_number = source_node->number;
    if (to_find == NEXT_BIGGEST)
        return (find_next_biggest(list_a, source_number));
    // else
    //     return (find_next_smallest(list_a, source_number));
    return (0);
}

int calculate_median(t_list_a *list_a)
{
    int median;
    
    median = 0;
    if (ft_lstsize(list_a) % 2 == 0)
    {
        printf("%d", 6 / 2);
        median = ft_lstsize(list_a) / 2;
    }
    else
        median = (ft_lstsize(list_a) / 2) + 1;
    return (median);
}