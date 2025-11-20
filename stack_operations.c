#include "push_swap.h"

bool    ft_is_sorted(t_list_a *list)
{
    while (list->next != NULL)
    {
        if (list->number > list->next->number)
            return (false);
        list = list->next;
    }
    return (true);
}

/*This function adds element to the b stack, starting from the bottom
and adding them always at the top*/
void    pb(t_list_a **list_a, t_list_a **list_b, int mode)
{
    t_list_a *temp;
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

void    pa(t_list_a **list_a, t_list_a **list_b, int mode)
{
    t_list_a *temp;
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
void    sa(t_list_a **list, int mode)
{
    int temp_number;
    int temp_index;

    temp_number = 0;
    temp_index = 0;
    temp_number = (*list)->number;
    temp_index = (*list)->index;
    (*list)->number = (*list)->next->number;
    (*list)->index = (*list)->next->index;
    (*list)->next->number= temp_number;
    (*list)->next->index = temp_index;
    if (mode == PRINT_IT)
        ft_printf("sa\n");
}

void    rra(t_list_a **list, int mode)
{
    t_list_a *node;
    t_list_a *prev;

    node = *list;
    prev = ft_lstlast(*list);
    prev = prev->prev;
    *list = ft_lstlast(*list);
    node->prev = *list;
    (*list)->next = node;
    (*list)->prev = NULL;
    prev->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("rra\n");
}

void    rrb(t_list_a **list, int mode)
{
    t_list_a *node;
    t_list_a *prev;

    node = *list;
    prev = ft_lstlast(*list);
    prev = prev->prev;
    *list = ft_lstlast(*list);
    node->prev = *list;
    (*list)->next = node;
    (*list)->prev = NULL;
    prev->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("rrb\n");
}
void    ra(t_list_a **list, int mode)
{
    t_list_a *first_temp;
    t_list_a *last_temp;

    first_temp = (*list);
    last_temp = ft_lstlast(*list);
    *list = (*list)->next;
    last_temp->next = first_temp;
    first_temp->prev = last_temp;
    first_temp->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("ra\n");
}

void    rb(t_list_a **list, int mode)
{
    t_list_a *first_temp;
    t_list_a *last_temp;

    first_temp = (*list);
    last_temp = ft_lstlast(*list);
    *list = (*list)->next;
    last_temp->next = first_temp;
    first_temp->prev = last_temp;
    first_temp->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("rb\n");
}
void rr(t_list_a **list_a, t_list_a **list_b)
{
    ra(list_a, 0);
    rb(list_b, 0);
    ft_printf("rr\n");
}
void rrr(t_list_a **list_a, t_list_a **list_b)
{
    rra(list_a, 0);
    rrb(list_b, 0);
    ft_printf("rrr\n");
}