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
    if (!ft_is_sorted(list))
    {
        printf("%zu\n", ft_lstsize(list));
        if (ft_lstsize(list) == 2)
            sort_two(&list);
        if (ft_lstsize(list) == 3)
            sort_three(&list);
        if (lstsize >= 4)
            sort_turks(&list_a, &list_b);
        while (list != NULL)
        {
            printf("%d", list->number);
            printf("\n");
            list = list->next;
        }
    }
    printf("True");
    // printf("%d\n", INT_MAX);
    // printf("%d\n", INT_MIN);
    return (0);
}