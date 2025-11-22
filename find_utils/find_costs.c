#include "../push_swap.h"

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