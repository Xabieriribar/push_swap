#include "push_swap.h"
int main(int argc, char **argv)
{
    int *numbers;

    if (!ft_parse_input(argc, argv, &numbers))
    {
        printf("False");
        return (false);
    }
    printf("True");
}