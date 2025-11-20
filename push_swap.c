#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;
    t_list_a    *list_a;
    t_list_a    *list_b;
    t_data      *data;

    list_a = NULL;
    list_b = NULL;
    data = malloc(sizeof(struct s_data));
    if (!data)
        return (0);
    data->argc = argc;
    data->argv = argv;
    data->mode = 0;
    if (!ft_parse_input(data, &numbers))
    {
        write(2, "Error", 5);
        return (0);
    }
    make_list(&list_a, numbers, data->argc);
    if (!ft_is_sorted(list_a))
    {
        if (ft_lstsize(list_a) == 2)
            sort_two(&list_a);
        if (ft_lstsize(list_a) == 3)
            sort_three(&list_a);
        if (ft_lstsize(list_a) >= 4)
            sort_turks(&list_a, &list_b);
    }
    ft_lstclear(&list_b);
    print_list(list_a);
    return (0);
}