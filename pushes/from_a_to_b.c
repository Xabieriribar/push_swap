#include "../push_swap.h"

void    from_a_to_b(t_list **list_a, t_list **list_b)
{
    int mode;
    int index_to_push_b;
    t_list *smallest_to_push;
    
    mode = 0;
    index_to_push_b = 0;
    while (ft_lstsize(*list_a) > 3)
    {
        while (index_to_push_b < 2 || mode == 0)
        {
            pb(list_a, list_b, PRINT_IT);
            index_to_push_b++;
            mode = 1;
        }
        update_indexes(list_a, list_b);
        assign_target_nodes_to_a(list_a, list_b);
        update_indexes(list_a, list_b);
        smallest_to_push = find_cost(*list_a, ft_lstsize(*list_a), ft_lstsize(*list_b));
        update_indexes(list_a, list_b);
        push_to_top(smallest_to_push, list_a, list_b);
        pb(list_a, list_b, PRINT_IT);
    }
}