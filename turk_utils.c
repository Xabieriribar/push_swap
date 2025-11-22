#include "push_swap.h"

int     set_costs(int index_a, int index_target, int len_a, int len_b)
{
    int cost_1;
    int cost_2;
    int cost_3;
    int cost_4;

    // Costo Sincronizado UP/UP
    cost_1 = MAX(index_a, index_target);
    // Costo Sincronizado DOWN/DOWN
    cost_2 = MAX(len_a - index_a, len_b - index_target);
    
    // Costo Oposición A up / B down
    cost_3 = index_a + (len_b - index_target);
    // Costo Oposición A down / B up
    cost_4 = (len_a - index_a) + index_target;

    return (MIN(MIN(cost_1, cost_2), MIN(cost_3, cost_4)));
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
                ra(list_a, PRINT_IT);
                update_indexes(list_a, NULL);
            }
        }
        else
        {
            while (smallest->index != 0)
            {
                rra(list_a, PRINT_IT);
                update_indexes(list_a, NULL);
            }
        }
        temp_a = temp_a->next;
    }
}

void    is_target_below_or_above(t_list_a *target_node, t_list_a **list_a, t_list_a **list_b, int mode, int print)
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
void    from_b_to_a(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *target_node;

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

    lowest_cost_node = list_a; // Inicializa con el primer nodo

    while (list_a != NULL)
    {
        // 1. CONDICIÓN PRINCIPAL: Si el costo actual es estrictamente menor
        if (list_a->cost < lowest_cost_node->cost)
            lowest_cost_node = list_a;
        
        // 2. CONDICIÓN DE DESEMPATE: Si los costos son iguales, elige el de menor índice
        else if (list_a->cost == lowest_cost_node->cost && list_a->index < lowest_cost_node->index)
            lowest_cost_node = list_a;

        list_a = list_a->next;
    }
    return (lowest_cost_node);
}

void    push_to_top(t_list_a *smallest_to_push, t_list_a **list_a, t_list_a **list_b)
{
    if (calculate_median(*list_a) >= smallest_to_push->index && calculate_median(*list_b) >= smallest_to_push->target_node->index)
    {
        while (smallest_to_push->index != 0 && smallest_to_push->target_node->index != 0)   
        {
            rr(list_a, list_b);
            update_indexes(list_a, list_b);
        }
        while (smallest_to_push->index != 0)
        {
            ra(list_a, PRINT_IT);
            update_indexes(list_a, list_b);
        }
        while (smallest_to_push->target_node->index != 0)
        {
            rb(list_b, PRINT_IT);
            update_indexes(list_a, list_b);
        }
    }
    else if (calculate_median(*list_a) < smallest_to_push->index && calculate_median(*list_b) < smallest_to_push->target_node->index)
    {
        while(smallest_to_push->index != 0 && smallest_to_push->target_node->index != 0)
        {
            rrr(list_a, list_b);
            update_indexes(list_a, list_b);
        }
        while(smallest_to_push->index != 0)
        {
            rra(list_a, PRINT_IT);
            update_indexes(list_a, list_b);
        }
        while(smallest_to_push->target_node->index != 0)
        {
            rrb(list_b, PRINT_IT);
            update_indexes(list_a, list_b);
        }
    }
    else
    {
        if (calculate_median(*list_a) < smallest_to_push->index && calculate_median(*list_b) >= smallest_to_push->target_node->index)
        {
            while (smallest_to_push->index != 0)
            {
                rra(list_a, PRINT_IT);
                update_indexes(list_a, list_b);
            }
            while (smallest_to_push->target_node->index != 0)
            {
                rb(list_b, PRINT_IT);
                update_indexes(list_a, list_b);
            }
        }
        else if (calculate_median(*list_a) >= smallest_to_push->index && calculate_median(*list_b) < smallest_to_push->target_node->index)
        {
            while(smallest_to_push->index != 0)
            {
                ra(list_a, PRINT_IT);
                update_indexes(list_a, list_b);
            }
            while(smallest_to_push->target_node->index != 0)
            {
                rrb(list_b, PRINT_IT);
                update_indexes(list_a, list_b);
            }
        }
    }
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