#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;
    t_list_a    *list;

    list = NULL;
    if (!ft_parse_input(argc, argv, &numbers))
    {
        printf("False");
        return (false);
    }
    make_list(&list, numbers);
    while (list != NULL)
    {
        printf("%d", list->number);
        printf("\n");
        list = list->next;
    }
    // printf("%d\n", INT_MAX);
    // printf("%d\n", INT_MIN);
    return (0);
}