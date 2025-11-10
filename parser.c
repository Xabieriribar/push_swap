#include "push_swap.h"

bool ft_is_number(int argc, char **argv, int **numbers, int mode)
{
    int index;
    int j;

    index = 1;
    j = 0;
    if (mode)
    {
        index = 0;
        argc += 1;
    }
    *numbers = malloc(sizeof(int) * (argc - 1));
    if (!*numbers)
        return (false);
    while (argv[index])
    {
        (*numbers)[j] = ft_atoi(argv[index]);
        if (!(*numbers)[j])
            return (false);
        j++;
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

bool    ft_int_overflow(char **argv)
{
    int index;

    index = 0;
    while (argv[index])
    {
        if (ft_strncmp(argv[index], "2147483647", 0) || ft_strncmp(argv[index], "-2147483648", 0))
            return (false);
        index++;
    }
    return (true);
}

bool    ft_parse_input(int argc, char **argv, int **numbers)
{
    int mode;
    
    mode = 0;
    if (argc == 2 && ft_strchr(argv[1], ' '))
    {
        argv = ft_split(argv[1], ' ');
        mode = 1;
    }
    if (argc == 1 || !ft_int_overflow(argv) || !ft_is_number(argc, argv, numbers, mode) || !ft_is_duplicate(numbers))
        return (false);
    return (true);
}