#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;
    t_list_a    *list_a;
    t_list_a    *list_b;
    t_data      *data;
    size_t lstsize;

    list_a = NULL;
    list_b = NULL;
    lstsize = 0;
    data = malloc(sizeof(struct s_data));
    if (!data)
        return (0);
    data->argc = argc;
    data->argv = argv;
    data->mode = 0;
    if (!ft_parse_input(data, &numbers))
    {
        printf("False");
        return (false);
    }
    make_list(&list_a, numbers, data->argc);
    if (!ft_is_sorted(list_a))
    {
        printf("%zu\n", ft_lstsize(list_a));
        if (ft_lstsize(list_a) == 2)
            sort_two(&list_a);
        if (ft_lstsize(list_a) == 3)
            sort_three(&list_a);
        if (ft_lstsize(list_a) >= 4)
            sort_turks(&list_a, &list_b);
        // while (list_a != NULL)
        // {
        //     printf("%d", list_a->number);
        //     printf("\n");
        //     list_a = list_a->next;
        // }
        // printf("%d", list_b->number);
    }
    printf("True");
    // printf("%d\n", INT_MAX);
    // printf("%d\n", INT_MIN);
    return (0);
}