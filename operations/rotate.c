#include "../push_swap.h"

void    ra(t_list **list, int mode)
{
    t_list *first_temp;
    t_list *last_temp;

    first_temp = (*list);
    last_temp = ft_lstlast(*list);
    *list = (*list)->next;
    last_temp->next = first_temp;
    first_temp->prev = last_temp;
    first_temp->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("ra\n");
}

void    rb(t_list **list, int mode)
{
    t_list *first_temp;
    t_list *last_temp;

    first_temp = (*list);
    last_temp = ft_lstlast(*list);
    *list = (*list)->next;
    last_temp->next = first_temp;
    first_temp->prev = last_temp;
    first_temp->next = NULL;
    if (mode == PRINT_IT)
        ft_printf("rb\n");
}
void rr(t_list **list_a, t_list **list_b)
{
    ra(list_a, 0);
    rb(list_b, 0);
    ft_printf("rr\n");
}