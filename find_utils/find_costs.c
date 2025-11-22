#include "../push_swap.h"

t_list *return_lowest_cost_node(t_list *list_a)
{
    t_list *lowest_cost_node;

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

t_list *find_cost(t_list *list_a, int len_a, int len_b)
{
    t_list *target_b;
    t_list *head_list;

    head_list = list_a;
    while (list_a != NULL)
    {
        target_b = list_a->target_node;
        list_a->cost = set_costs(list_a->index, target_b->index, len_a, len_b);
        list_a = list_a->next;
    }
    return (return_lowest_cost_node(head_list));
}