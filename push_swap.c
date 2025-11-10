#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;
    t_list_a    *list;
    size_t lstsize;

    list = NULL;
    lstsize = 0;
    if (!ft_parse_input(argc, argv, &numbers))
    {
        printf("False");
        return (false);
    }
    make_list(&list, numbers, &lstsize, argc);
    if (!ft_is_sorted(list))
    {
        printf("%zu\n", lstsize);
        if (lstsize == 2)
            sa(&list);
        // if (lstsize == 3)
        // {
        //     sort_three(list);
        //     return (0);
        // }
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