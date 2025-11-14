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
void    pb(t_list_a **list_a, t_list_a **list_b)
{
    t_list_a *node;

    node = *list_a;
    *list_a = (*list_a)->next;
    if (*list_a)
        (*list_a)->prev = NULL;
    if (!*list_b)
    {
        node->next = NULL;
        node->prev = NULL;
        *list_b = node;
    }
    else
    {
        node->next = (*list_b);
        node->prev = NULL;
        (*list_b)->prev = node;
        *list_b = node;
    }
}
void    sa(t_list_a **list)
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
    ft_printf("sa\n");
}

void    rra(t_list_a **list)
{
    int temp_n;
    int first_n;
    int temp_next;
    t_list_a *last;
    t_list_a *temp;

    last = ft_lstlast(*list);
    first_n = (*list)->number;
    temp = *list;
    while (temp ->next->next != NULL)
    {
        if (temp->number == first_n)
        {
            temp_n = temp->number;
            temp->number = last->number;
            continue;
        }
        temp_next = temp->next->number;
        temp->next->number = temp_n;
        temp->next->next->number = temp_next;
        temp = temp->next;
    }
    ft_printf("rra\n");
}
void    ra(t_list_a **list)
{
    t_list_a *first_temp;
    t_list_a *last_temp;

    first_temp = (*list);
    last_temp = ft_lstlast(*list);
    *list = (*list)->next;
    last_temp->next = first_temp;
    first_temp->next = NULL;
    ft_printf("ra\n");
}