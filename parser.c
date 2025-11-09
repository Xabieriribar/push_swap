#include "push_swap.h"

bool ft_is_number(int argc, char **argv, int **numbers)
{
    int index;

    index = 1;
    *numbers = malloc(sizeof(int) * (argc - 1));
    if (!*numbers)
        return (false);
    while (argv[index])
    {
        (*numbers)[index - 1] = ft_atoi(argv[index]);
        if (!(*numbers)[index - 1])
            return (false);
        index++;
    }
    return (true);
}

bool    ft_is_duplicate(int **numbers)
{
    int  index;
    int  jndex;

    index = 0;
    while ((*numbers)[index]) 
    {
        jndex = index + 1;
        while ((*numbers)[jndex])
        {
            if ((*numbers)[index] == (*numbers)[jndex])
                return (false);
            jndex++;
        }
        index++;
    }
    return (true);
}

bool    ft_parse_input(int argc, char **argv, int **numbers)
{
    if (argc <= 2 || !ft_is_number(argc, argv, numbers) || !ft_is_duplicate(numbers))
        return (false);
    return (true);
}