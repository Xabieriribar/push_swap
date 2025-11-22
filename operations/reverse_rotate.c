#include "../push_swap.h"

void    rra(t_list **list, int mode)
{
    t_list *node;
    t_list *prev;

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

void    rrb(t_list **list, int mode)
{
    t_list *node;
    t_list *prev;

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

void rrr(t_list **list_a, t_list **list_b)
{
    rra(list_a, 0);
    rrb(list_b, 0);
    ft_printf("rrr\n");
}