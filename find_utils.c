#include "push_swap.h"

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
// t_list_a *find_node_with_smallest_cost(t_list_a **list_a, t_list_a **list_b)
// {
//     t_list_a *temp_list_b;
//     t_list_a *temp_list_a;
//     t_list_a *temp_temp_list_a;
//     t_list_a *temp_node;

//     temp_list_b = copy_list(*list_b);
//     temp_list_a = copy_list(*list_a);
//     temp_list_a->cost = 0;
//     temp_list_b->cost = 0;
//     t_list_a *save_list_a = temp_list_a;
//     while (temp_list_a != NULL)
//     {
//         temp_node = temp_list_a;
//         temp_temp_list_a = copy_list(*list_a);
//         if (calculate_median(temp_list_a) >= temp_node->index)
//         {
//             while (temp_node->index != 0)
//             {
//                 ra(&temp_temp_list_a, 0);
//                 update_indexes(&temp_temp_list_a, NULL);
//                 temp_list_a->cost++;
//                 temp_node->index--;
//             }
//         }
//         else if (calculate_median(temp_list_a) < temp_node->index)
//         {
//             while(temp_node->index != (int)ft_lstsize(*list_a))
//             {
//                 rra(&temp_temp_list_a, 0);
//                 update_indexes(&temp_temp_list_a, NULL);
//                 temp_list_a->cost++;
//                 temp_node->index++;
//             }
//         }
//         temp_list_a = temp_list_a->next;
//     }
//     temp_list_a = save_list_a;
//     while (temp_list_a != NULL)
//     {
//         temp_node = temp_list_a->target_node;
//         temp_list_b = copy_list(*list_b);
//         if (calculate_median(*list_b) >= temp_node->index)
//         {
//             while(temp_node->index != 0)
//             {
//                 ra(&temp_list_b, 0);
//                 update_indexes(NULL, &temp_list_b);
//                 temp_list_a->cost++;
//                 temp_node->index--;
//             }
//         }
//         else if (calculate_median(*list_b) > temp_node->index)
//         {
//             while (temp_node->index != (int)ft_lstsize(*list_b))
//             {
//                 rra(&temp_list_b, 0);
//                 update_indexes(NULL, &temp_list_b);
//                 temp_list_a->cost++;
//                 temp_node->index++;
//             }
//         }
//         temp_list_a = temp_list_a->next;
//     }
//     temp_list_a = save_list_a;
//     update_indexes(&temp_list_a, NULL);
//     return (return_lowest_cost_node(temp_list_a));
//     // exit(EXIT_SUCCESS);
// }
t_list_a *find_cost(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp_list;
    t_list_a *head_temp_list;
    t_list_a *target_b;
    int len_a;
    int len_b;

    len_a = ft_lstsize(*list_a);
    len_b = ft_lstsize(*list_b);
    temp_list = *list_a;
    head_temp_list = temp_list;
    while (temp_list != NULL)
    {
        target_b = temp_list->target_node;
        // 1. Calcula las 4 rutas combinadas (Usando variables auxiliares)
        int cost_ra = temp_list->index; 
        int cost_rb = target_b->index;
        int cost_rra = len_a - temp_list->index; 
        int cost_rrb = len_b - target_b->index;
        
        // Costo Sincronizado UP/UP
        int cost_1 = MAX(cost_ra, cost_rb);
        // Costo Sincronizado DOWN/DOWN
        int cost_2 = MAX(cost_rra, cost_rrb);
        
        // Costo Oposición A up / B down
        int cost_3 = cost_ra + cost_rrb;
        // Costo Oposición A down / B up
        int cost_4 = cost_rra + cost_rb;
        
        // 2. Asigna el MÍNIMO de las 4 opciones
        temp_list->cost = MIN(MIN(cost_1, cost_2), MIN(cost_3, cost_4));

        temp_list = temp_list->next;
    }
    return (head_temp_list);
}

t_list_a *find_node_with_smallest_cost(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *temp_list;

    temp_list = find_cost(list_a, list_b);
    return (return_lowest_cost_node(temp_list));
}