#include "push_swap.h"

void  ft_lstnew_a(t_list_a **new_node_a, t_list_b **new_node_b, int number, int index)
{
    t_list_a    *new_node;

    new_node->number = number;
    new_node->index = index;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

t_list_b  *ft_lstnew_b(int number, int index)
{
    t_list_b    *new_node;

    new_node->number = number;
    new_node->index = index;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

void    ft_lstadd_back(t_list_a *list, int number, int index, int mode)
{
    t_list_a    *list_a;
    t_list_b    *list_b;

    if (mode == 1)
    {
        list_b = list_b;
        if (list_a == NULL)
        {
            list = ft_lstnew_a(number, index, mode);
            return ;
        }
        list->prev = list_a;
        list->next = NULL;
        list->number = number;
        list->index = index;
    }
    else
    {
        list_a = list_a;
        if (list_b == NULL)
        {
            list = ft_lstnew(number, index, mode);
            return ;
        }
        list->prev = list_b;
        list->next = NULL;
        list->number = number;
        list->index = index;
    }

}

t_list_b    ft_lstadd_back_b(t_list_a *list, int number, int index)
{
    t_list_a    *list_b;

    if (list_b == NULL)
    {
        list = ft_lstnew_a(number, index);
        return ;
    }
    list->prev = list_b;
    list->next = NULL;
    list->number = number;
    list->index = index;
}
