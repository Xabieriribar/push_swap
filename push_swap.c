#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;
    t_operations *operations;
    t_list_a    *list;
    size_t lstsize;
    int index = 0;

    list = NULL;
    operations = malloc(sizeof(struct s_operations));
    if (!operations)
        return (0);
    operations->index = 0;
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
            sort_two(&list, operations);
        if (lstsize == 3)
            sort_three(&list, operations);
        while (operations->operation_list[index] != NULL)
            printf("%s\n", operations->operation_list[index++]);
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