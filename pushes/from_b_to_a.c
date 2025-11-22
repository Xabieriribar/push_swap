#include "../push_swap.h"

void    from_b_to_a(t_list **list_a, t_list **list_b)
{
    t_list *target_node;

    while (ft_lstsize(*list_b) > 0)
    {
        target_node = get_target_node(*list_a, *list_b, NEXT_BIGGEST);
        if (target_node->index == 0)
        {
            pa(list_a, list_b, PRINT_IT);
            update_indexes(list_a, list_b);
        }
        else
            is_target_below_or_above(target_node, list_a, list_b, PUSH_A, PRINT_IT);
        update_indexes(list_a, list_b);
    }
}