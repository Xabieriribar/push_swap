#include "../push_swap.h"

void    pb(t_list **list_a, t_list **list_b, int mode)
{
    t_list *temp;
    if (!*list_a)
        return;
    temp = *list_a;           // Take the top node of source
    *list_a = (*list_a)->next;   // Move source head down
    if (*list_a)
        (*list_a)->prev = NULL;
    
    temp->next = *list_b;    // Link temp to the old head of dest
    if (*list_b)
        (*list_b)->prev = temp;
    *list_b = temp;
    if (mode == PRINT_IT)
        ft_printf("pb\n");
}

void    pa(t_list **list_a, t_list **list_b, int mode)
{
    t_list *temp;
    if (!*list_b)
        return;
    temp = *list_b;           // Take the top node of source
    *list_b = (*list_b)->next;   // Move source head down
    if (*list_b)
        (*list_b)->prev = NULL;
    
    temp->next = *list_a;    // Link temp to the old head of dest
    if (*list_a)
        (*list_a)->prev = temp;
    *list_a = temp;
    if (mode == PRINT_IT)
        ft_printf("pa\n");
}