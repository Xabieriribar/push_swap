#include "push_swap.h"

bool    ft_parse_input(int argc, char **argv, int **numbers)
{
    int  index;
    int  jndex;


    if (argc == 1)
        return (false);
    *numbers = malloc(sizeof(int) * (argc - 1));
    if (!*numbers)
        return (false);
    index = 1;
    while (argv[index])
    {
        (*numbers)[index - 1] = ft_atoi(argv[index]);
        if (!(*numbers)[index - 1])
            return (false);
        index++;
    }
    index = 1;
    while ((*numbers)[index - 1]) 
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