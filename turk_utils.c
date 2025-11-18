#include "push_swap.h"

void print_list(t_list_a *list)
{
    printf("Printing list...\n");
    while (list != NULL)
    {
        printf("Digit %d with index %d\n", list->number, list->index);
        list = list->next;
    }
    printf("\n");
}

void    update_indexes(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp;
    int     index; 

    if (list_a != NULL)
    {
        index = 0;
        temp = *list_a;
        while (temp != NULL)
        {
            temp->index = index;
            index++;
            temp = temp->next;
        }
    }
    if (list_b == NULL)
        return ;
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
t_list_a *get_target_node(t_list_a *list, t_list_a *source_node, int to_find)
{
    int source_number;
    
    source_number = source_node->number;
    if (to_find == NEXT_BIGGEST)
        return (find_next_biggest(list, source_number));
    else if (to_find == NEXT_SMALLEST)
        return (find_next_smallest(list, source_number));
    return (0);
}

int calculate_median(t_list_a *list_a)
{
    int median;
    
    median = 0;
    if (ft_lstsize(list_a) % 2 == 0)
    {
        median = ft_lstsize(list_a) / 2;
    }
    else
        median = (ft_lstsize(list_a) / 2) + 1;
    return (median);
}

void    sort_smallest(t_list_a **list_a)
{
    t_list_a *temp_a;
    t_list_a *smallest;

    temp_a = *list_a;
    while (temp_a != NULL)
    {
        smallest = find_smallest(*list_a);
        if (calculate_median(*list_a) > smallest->index)
        {
            while (smallest->index != 0)
            {
                ra(list_a);
                update_indexes(list_a, NULL);
            }
        }
        else
        {
            while (smallest->index != 0)
            {
                rra(list_a);
                update_indexes(list_a, NULL);
            }
        }
        temp_a = temp_a->next;
    }
}

void    is_target_below_or_above(t_list_a *target_node, t_list_a **list_a, t_list_a **list_b, int mode)
{
    if (calculate_median(*list_a) >= target_node->index)
    {
        while (target_node->index != 0)
        {
            ra(list_a);
            update_indexes(list_a, NULL);
        }
        if (mode == PUSH_A)
            pa(list_a, list_b);
        else
            pb(list_a, list_b);
    }
    else
    {
        while (target_node->index != 0)
        {
            rra(list_a);
            update_indexes(list_a, list_b);
        }
        if (mode == PUSH_A)
            pa(list_a, list_b);
        else
            pb(list_a, list_b);
    }
}
void    from_b_to_a(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp_b;
    t_list_a *target_node;

    temp_b = *list_b;
    while (temp_b != NULL && *list_b)
    {
        target_node = get_target_node(*list_a, *list_b, NEXT_BIGGEST);
        if (target_node->index == 0)
        {
            pa(list_a, list_b);
            update_indexes(list_a, list_b);
        }
        else
            is_target_below_or_above(target_node, list_a, list_b, PUSH_A);
        temp_b = temp_b->next;
        update_indexes(list_a, list_b);
    }
}
void    assign_target_nodes_to_a(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *target_nodes;
    t_list_a *temp_a;

    temp_a = *list_a;
    while (temp_a != NULL)
    {
        target_nodes = get_target_node(*list_b, temp_a, NEXT_SMALLEST);
        temp_a->target_node = target_nodes;
        temp_a = temp_a->next;
    }
}
t_list_a *return_lowest_cost_node(t_list_a *list_a)
{
    t_list_a *lowest_cost_node;
    int         mode;

    mode = 0;
    lowest_cost_node = list_a;
    while (list_a != NULL)
    {
        if (lowest_cost_node->cost > list_a->cost && (lowest_cost_node->index < list_a->index || mode == 0))
        {
            mode = 1;
            lowest_cost_node = list_a;
        }
        list_a = list_a->next;
    }
    return (lowest_cost_node);
}
t_list_a *find_node_with_smallest_cost(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp_list_b;
    t_list_a *temp_list_a;
    t_list_a *temp_temp_list_a;
    t_list_a *temp_node;

    temp_list_b = copy_list(*list_b);
    temp_list_a = copy_list(*list_a);
    temp_list_a->cost = 0;
    temp_list_b->cost = 0;
    t_list_a *save_list_a = temp_list_a;
    while (temp_list_a != NULL)
    {
        temp_node = temp_list_a;
        temp_temp_list_a = copy_list(*list_a);
        if (calculate_median(temp_list_a) >= temp_node->index)
        {
            while (temp_node->index != 0)
            {
                ra(&temp_temp_list_a);
                update_indexes(&temp_temp_list_a, NULL);
                temp_list_a->cost++;
                temp_node->index--;
            }
        }
        else if (calculate_median(temp_list_a) < temp_node->index)
        {
            while(temp_node->index != (int)ft_lstsize(*list_a))
            {
                rra(&temp_temp_list_a);
                update_indexes(&temp_temp_list_a, NULL);
                temp_list_a->cost++;
                temp_node->index++;
            }
        }
        temp_list_a = temp_list_a->next;
    }
    temp_list_a = save_list_a;
    while (temp_list_a != NULL)
    {
        temp_node = temp_list_a->target_node;
        temp_list_b = copy_list(*list_b);
        if (calculate_median(*list_b) >= temp_node->index)
        {
            while(temp_node->index != 0)
            {
                ra(&temp_list_b);
                update_indexes(NULL, &temp_list_b);
                temp_list_a->cost++;
                temp_node->index--;
            }
        }
        else if (calculate_median(*list_b) > temp_node->index)
        {
            while (temp_node->index != (int)ft_lstsize(*list_b))
            {
                rra(&temp_list_b);
                update_indexes(NULL, &temp_list_b);
                temp_list_a->cost++;
                temp_node->index++;
            }
        }
        temp_list_a = temp_list_a->next;
    }
    temp_list_a = save_list_a;
    update_indexes(&temp_list_a, NULL);
    return (return_lowest_cost_node(temp_list_a));
    // exit(EXIT_SUCCESS);
}
void    from_a_to_b(t_list_a **list_a, t_list_a **list_b)
{
    int mode;
    int index_to_push_b;
    t_list_a *smallest_to_push;
    
    mode = 0;
    index_to_push_b = 0;
    while (ft_lstsize(*list_a) > 3)
    {
        while (index_to_push_b < 2 || mode == 0)
        {
            pb(list_a, list_b);
            index_to_push_b++;
            mode = 1;
        }
        update_indexes(list_a, list_b);
        assign_target_nodes_to_a(list_a, list_b);
        update_indexes(list_a, list_b);
        smallest_to_push = find_node_with_smallest_cost(list_a, list_b);
        if (smallest_to_push->index != 0)
            pb(list_a, list_b);
        else
            is_target_below_or_above(smallest_to_push, list_a, list_b, PUSH_B);
    }
}