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
    t_list_a *target_node;
    while (ft_lstsize(*list_a) > 3)
    {
        pb (list_a, list_b);
    }
    if (!ft_is_sorted(*list_a))
        sort_three(list_a);
    update_indexes(list_a, list_b);
    t_list_a *temp_a = *list_a;
    printf("List a\n");
    while (temp_a != NULL)
    {
        printf("Digit: %d, with index %d\n", temp_a->number, temp_a->index);
        temp_a = temp_a->next;
    }
    t_list_a *temp_b = *list_b;
    printf("List b\n");
    while (temp_b != NULL)
    {
        printf("Digit: %d, with index %d\n", temp_b->number, temp_b->index);
        temp_b = temp_b->next;
    }
    target_node = get_target_node(*list_a, *list_b, NEXT_BIGGEST);
    printf("The closest biggest is %d", target_node->number);
}
