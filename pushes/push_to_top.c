#include "../push_swap.h"


void    loop_if_below_median(t_list *smallest_to_push, t_list *target_node, t_list **list_a, t_list **list_b)
{
    while(smallest_to_push->index != 0 && target_node->index != 0)
    {
        rrr(list_a, list_b);
        update_indexes(list_a, list_b);
    }
    while(smallest_to_push->index != 0)
    {
        rra(list_a, PRINT_IT);
        update_indexes(list_a, list_b);
    }
    while(target_node->index != 0)
    {
        rrb(list_b, PRINT_IT);
        update_indexes(list_a, list_b);
    }
}

void    high_cost_loop_one(t_list *smallest_to_push, t_list *target_node, t_list **list_a, t_list **list_b)
{
    while (smallest_to_push->index != 0)
    {
        rra(list_a, PRINT_IT);
        update_indexes(list_a, list_b);
    }
    while (target_node->index != 0)
    {
        rb(list_b, PRINT_IT);
        update_indexes(list_a, list_b);
    }
}
void    loop_if_above_median(t_list *smallest_to_push, t_list *target_node, t_list **list_a, t_list **list_b)
{
    while (smallest_to_push->index != 0 && target_node->index != 0)   
    {
        rr(list_a, list_b);
        update_indexes(list_a, list_b);
    }
    while (smallest_to_push->index != 0)
    {
        ra(list_a, PRINT_IT);
        update_indexes(list_a, list_b);
    }
    while (target_node->index != 0)
    {
        rb(list_b, PRINT_IT);
        update_indexes(list_a, list_b);
    }
}
void high_cost_loop_two(t_list *smallest_to_push, t_list *target_node, t_list **list_a, t_list **list_b)
{
    while(smallest_to_push->index != 0)
    {
        ra(list_a, PRINT_IT);
        update_indexes(list_a, list_b);
    }
    while(target_node->index != 0)
    {
        rrb(list_b, PRINT_IT);
        update_indexes(list_a, list_b);
    }
}
void    push_to_top(t_list *smallest_to_push, t_list **list_a, t_list **list_b)
{
    if (calculate_median(*list_a) >= smallest_to_push->index && calculate_median(*list_b) >= smallest_to_push->target_node->index)
        loop_if_above_median(smallest_to_push, smallest_to_push->target_node, list_a, list_b);
    else if (calculate_median(*list_a) < smallest_to_push->index && calculate_median(*list_b) < smallest_to_push->target_node->index)
        loop_if_below_median(smallest_to_push, smallest_to_push->target_node, list_a, list_b);
    else
    {
        if (calculate_median(*list_a) < smallest_to_push->index && calculate_median(*list_b) >= smallest_to_push->target_node->index)
            high_cost_loop_one(smallest_to_push, smallest_to_push->target_node, list_a, list_b);
        else if (calculate_median(*list_a) >= smallest_to_push->index && calculate_median(*list_b) < smallest_to_push->target_node->index)
            high_cost_loop_two(smallest_to_push, smallest_to_push->target_node, list_a, list_b);
    }
}