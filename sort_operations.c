#include "push_swap.h"

void    sort_two(t_list_a **list)
{
    sa(list);
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

void    sort_turks(t_list_a **list_a, t_list_a **list_b)
{
    from_a_to_b(list_a, list_b);
    while (ft_lstsize(*list_a) > 3)
    {
        pb (list_a, list_b);
    }
    update_indexes(list_a, list_b);
    if (!ft_is_sorted(*list_a))
    {
        sort_three(list_a);
    }
    update_indexes(list_a, list_b);
    t_list_a *temp_b = *list_b;
    temp_b = *list_b;
    from_b_to_a(list_a, list_b);
    sort_smallest(list_a);
    update_indexes(list_a, list_b);
}
