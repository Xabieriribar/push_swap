#include "../push_swap.h"

t_list *get_target_node(t_list *list, t_list *source_node, int to_find)
{
    int source_number;
    
    source_number = source_node->number;
    if (to_find == NEXT_BIGGEST)
        return (find_next_biggest(list, source_number));
    else if (to_find == NEXT_SMALLEST)
        return (find_next_smallest(list, source_number));
    return (0);
}

void    is_target_below_or_above(t_list *target_node, t_list **list_a, t_list **list_b, int mode, int print)
{
    if (calculate_median(*list_a) >= target_node->index)
    {
        while (target_node->index != 0)
        {
            if (print == PRINT_IT)
                ra(list_a, PRINT_IT);
            update_indexes(list_a, NULL);
        }
        if (mode == PUSH_A)
            pa(list_a, list_b, PRINT_IT);
        else
            pb(list_a, list_b, PRINT_IT);
    }
    else
    {
        while (target_node->index != 0)
        {
            if (print == PRINT_IT)
                rra(list_a, PRINT_IT);
            update_indexes(list_a, list_b);
        }
        if (mode == PUSH_A)
            pa(list_a, list_b, PRINT_IT);
        else if (mode == PUSH_B)
            pb(list_a, list_b, PRINT_IT);
    }
}
void    assign_target_nodes_to_a(t_list **list_a, t_list **list_b)
{
    t_list *target_nodes;
    t_list *temp_a;

    temp_a = *list_a;
    while (temp_a != NULL)
    {
        target_nodes = get_target_node(*list_b, temp_a, NEXT_SMALLEST);
        temp_a->target_node = target_nodes;
        temp_a = temp_a->next;
    }
}