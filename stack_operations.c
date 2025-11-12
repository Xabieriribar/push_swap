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

void    sa(t_list_a **list, t_operations *operations)
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
    operations->operation_list[operations->index] = "sa";
}

void    rra(t_list_a **list, t_operations *operation)
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
    operation->operation_list[operation->index]= "rra";
}
void    ra(t_list_a **list, t_operations *operations)
{
    int first_number;
    t_list_a *last;

    first_number = (*list)->number;
    last = ft_lstlast(*list);
    (*list)->number = last->number;
    last->number = first_number;
    operations->operation_list[operations->index] = "ra";
}